#include <iostream>
#include <iomanip>
#include <cmath>
#include "dcmat.h"

using std::cout;
using std::fixed;

// Construtor
DCMat::DCMat()
{
    resetSettings();

    matrix = nullptr;
    matrixTemp = createMatrix();

    flagErro = false;
    flagUndefined = false;
}

// Desconstrutor
DCMat::~DCMat()
{
    delete matrixTemp;

    if(matrix != nullptr){
        delete matrix;
    }

    // Todos as matrizes da lista de simbolos
    for(auto& simbolo : symbols){
        if(simbolo.second.matriz != nullptr){
            delete simbolo.second.matriz;
        }
    }
}

void DCMat::setHView(double low, double high)
{
    if(low >= high){
        showErrorMessage("h_view_lo must be smaller than h_view_hi");
        // cout << low << high;
    }else{
        h_view.high = high;
        h_view.low = low;
    }
}

void DCMat::setVView(double low, double high)
{
    if(low >= high){
        showErrorMessage("v_view_lo must be smaller than v_view_hi");
        // cout << low << high;
    }else{
        v_view.high = high;
        v_view.low = low;
    }
}

void DCMat::setFloatPrecision(int precision)
{
    if(precision < 0 || precision > 8){
        showErrorMessage("float precision must be from 0 to 8");
    }else{
        float_precision = precision;
    }
}

void DCMat::setIntegralSteps(int steps)
{
    if(steps <= 0){
        showErrorMessage("integral_steps must be a positive non-zero integer");
    }else{
        integral_steps = steps;
    }
}

void DCMat::setDrawAxis(bool state)
{
    draw_axis = state;
}

void DCMat::setErasePlot(bool state)
{
    erase_plot = state;
}

void DCMat::setConnectDots(bool state)
{
    connect_dots = state;
}

/******************************************************
*       CONFIGURAÇÕES
*******************************************************/

void DCMat::showErrorMessage(string message)
{
    cout << "\nERROR: " << message << "\n\n";
}

void DCMat::showError(Erro error)
{
    switch (error)
    {
    case Erro::DividedByZero:
        cout << "\ninf";
        break;

    case Erro::VariableX:
        cout << "\nThe x variable cannot be present on expressions.";
        break;

    case Erro::UndefinedSymbol:
        cout << "\nUndefined symbol";
        break;

    case Erro::NoMatrix:
        cout << "\nNo matrix defined!";
        break;

    case Erro::MatrixLimits:
        showErrorMessage("Matrix limits out of boundaries.");
        break;    

    case Erro::MatrixFormat:
        cout << "\nMatrix format incorrect!";
        break;
    
    default:
        break;
    }
}

void DCMat::showAbout()
{
    cout << "\n+----------------------------------------------+";
    cout << "\n|                                              |";
    cout << "\n|              DCMAT - V. 2024.01              |";
    cout << "\n|         202200560356 - Isadora Vanço         |";
    cout << "\n|                                              |";
    cout << "\n+----------------------------------------------+";
}

void DCMat::showSettings()
{
    cout << "\nh_view_lo: " << fixed << std::setprecision(6) << h_view.low;
    cout << "\nh_view_hi: " << fixed << std::setprecision(6) << h_view.high;
    cout << "\nv_view_lo: " << fixed << std::setprecision(6) << v_view.low;
    cout << "\nv_view_hi: " << fixed << std::setprecision(6) << v_view.high;
    cout << "\nfloat_precision: " <<  float_precision;
    cout << "\nintegral_steps: " << integral_steps;
    
    cout << "\n\nDraw Axis: " << (draw_axis ? "ON" : "OFF");
    cout << "\nErase Plot: " << (erase_plot ? "ON" : "OFF");
    cout << "\nConnect Dots: " << (connect_dots ? "ON" : "OFF");
}

void DCMat::resetSettings()
{
    h_view.low = -6.5;
    h_view.high = 6.5;
    v_view.low = -3.5;
    v_view.high = 3.5;
    float_precision = 6;
    integral_steps = 1000;
    draw_axis = true;
    erase_plot = true;
    connect_dots = false;
}

/******************************************************
*       EXPRESSÕES
*******************************************************/

double DCMat::calculateValue(NodeArvore *root, bool variableX, double xValue)
{
    if(!root){
        return 0.0;
    }

    switch(root->tipo) 
    {
        case TipoElemento::FUNCAO: 
        {
            double valor = calculateValue(root->esquerda, variableX, xValue);
            
            if(root->id == "SEN"){
                return std::sin(valor);
            }else if (root->id == "COS"){
                return std::cos(valor);
            }else if (root->id == "TAN"){
                return std::tan(valor);
            }else if (root->id == "ABS"){
                return std::abs(valor);
            }
            break;
        }
        case TipoElemento::OPERADOR: 
        {
            double valorDir = calculateValue(root->direita, variableX, xValue);

            if(root->id == "+"){
                double valorEsq = calculateValue(root->esquerda, variableX, xValue);
                return valorEsq + valorDir;
            }else if (root->id == "-"){
                double valorEsq = calculateValue(root->esquerda, variableX, xValue);
                return valorEsq - valorDir;
            }else if (root->id == "*"){
                double valorEsq = calculateValue(root->esquerda, variableX, xValue);
                return valorEsq * valorDir;
            }else if (root->id == "/"){
                if (valorDir != 0) {
                    double valorEsq = calculateValue(root->esquerda, variableX, xValue);
                    return valorEsq / valorDir;
                }else{
                    flagErro = true;
                    showError(Erro::DividedByZero);
                    return 0.0;
                }
            }else if(root->id == "%"){
                if(valorDir != 0){
                    double valorEsq = calculateValue(root->esquerda, variableX, xValue);
                    return std::fmod(valorEsq, valorDir);
                }else{
                    flagErro = true;
                    showError(Erro::DividedByZero);
                    return 0.0;
                }
            }else if (root->id == "^"){
                double valorEsq = calculateValue(root->esquerda, variableX, xValue);
                return std::pow(valorEsq, valorDir);
            }
            break;
        }
        case TipoElemento::UNARIO: 
        {
            double valor = calculateValue(root->esquerda, variableX, xValue);
            
            if(root->id == "-"){
                return -valor;
            }
            return valor;
        }
        case TipoElemento::IDENTIFICADOR: 
        {
            if(!flagErro){
                return getSymbol(root->id);
            }
            return 0.0;
        }
        case TipoElemento::VARIAVEL_X: 
        {
            if(variableX){
                return xValue;
            }
            flagErro = true;
            return 0.0;
        }
        case TipoElemento::CONSTANTE: 
        {
            return root->numero;
        }
        default:
            break;
    }
}

void DCMat::showValue(double value)
{
    if(!flagErro && !flagUndefined){
        cout << "\n" << fixed << std::setprecision(float_precision) << value;
    }
    flagErro = false;
    flagUndefined = false;
}   

void DCMat::showRpnExpression(NodeArvore *root)
{
    cout << "\nExpression in RPN format:\n\n";
    showPostOrder(root, float_precision);
    freeNodes(root);
}

void DCMat::showExpression(NodeArvore *root)
{
    if(isXVariablePresent(root)){
        showError(Erro::VariableX);
    }else{
        double valor = calculateValue(root, false, 0);
        showValue(valor);
    }

    freeNodes(root);
}

/******************************************************
*       MATRIZ
*******************************************************/

int DCMat::countDigits(int number)
{
    if(number == 0){
        return 1; 
    }

    int total = 0;

    if (number < 0) {
        total++;
        number = -number;
    }

    total += static_cast<int>(std::log10(number)) + 1;

    return total;
}

void DCMat::showMatrix(Matriz *matriz)
{
    if(matriz == nullptr){
        matriz = matrix;
    }
    
    if(matriz == nullptr){
        showError(Erro::NoMatrix);
    }else{
        int numLinhas = matriz->linhas;
        int numColunas = matriz->colunas;
        int digitos[numLinhas + 1][numColunas];
        int somaLinha = 0;
        int digito;

        // Primeira linha 
        for(int j = 0; j < numColunas; j++){
            digito = countDigits(matriz->matriz[0][j]);
            
            digitos[0][j] = digito;
            // Maiores digitos
            digitos[numLinhas][j] = digito;
        }

        // Pega todas as quantidades da parte inteira dos números 
        for(int i = 1; i < numLinhas; i++){
            for(int j = 0; j < numColunas; j++){
                digito = countDigits(matriz->matriz[i][j]);
                digitos[i][j] = digito;

                if(digitos[i][j] > digitos[numLinhas][j]){
                    digitos[numLinhas][j] = digito;
                }
            }
        }

        // Quantidade de espaços entre os números
        somaLinha += numColunas - 1;

        // Quantidade de casas decimais e pontos
        if(float_precision > 0){
            somaLinha += numColunas * (float_precision + 1);
        }

        // Maiores dígitos
        for(int j = 0; j < numColunas; j++){
            somaLinha += digitos[numLinhas][j];
        }

        // Borda superior
        cout << "\n+-";
        for(int i = 0; i < somaLinha; i++){
            cout << " ";
        }
        cout << "-+";

        // Meios
        for(int i = 0; i < numLinhas; i++){
            cout << "\n|";
            for(int j = 0; j < numColunas; j++){
                cout << " ";

                int x = digitos[numLinhas][j] - digitos[i][j];
                // cout << " (" << x << ") ";
                for(x; x > 0; x--){
                    cout << " ";
                }

                cout << fixed << std::setprecision(float_precision) << matriz->matriz[i][j];
            }
            cout << " |";
        }

        // Borda inferior
        cout << "\n+-";
        for(int i = 0; i < somaLinha; i++){
            cout << " ";
        }
        cout << "-+";
    }
}

Matriz* DCMat::createMatrix()
{
    Matriz *matriz = new Matriz();
    matriz->colunas = 0;
    matriz->linhas = 0;
    resizeRows(matriz, 1);

    // Indices começam em 0
    iMatrix = 0;
    jMatrix = 0;

    return matriz;
}

void DCMat::resizeColumns(Matriz *matriz, int columns)
{
    if(columns > maxMatrix){
        showError(Erro::MatrixLimits);
        
        delete matrixTemp;
        matrixTemp = createMatrix();
        flagErro = true;
    }else{
        for (auto& linha : matriz->matriz) {
            linha.resize(columns, 0);
        }

        matriz->colunas = columns;
        // cout << "Novo tamanho: " << matriz->linhas << "x" << matriz->colunas << std::endl;
    }
}

void DCMat::resizeRows(Matriz *matriz, int rows)
{
    if(rows > maxMatrix){
        showError(Erro::MatrixLimits);
        
        delete matrixTemp;
        matrixTemp = createMatrix();
        flagErro = true;
    }else{
        matriz->matriz.resize(rows, vector<double>(matriz->colunas, 0));
        matriz->linhas = rows;
        // cout << "Novo tamanho: " << rows << "x" << matriz->colunas << std::endl;
    }
}

void DCMat::addColumnMatrix(double number)
{
    if(flagErro){
        return;
    }

    jMatrix++;
    // cout << "\ncol[" << iMatrix << "][" << jMatrix << "]" << std::endl;
    
    // cout << "Tamanho: " << matrixTemp->linhas << "x" << matrixTemp->colunas << std::endl;
    if(jMatrix > iMatrix){
        if(jMatrix > matrixTemp->colunas){
            resizeColumns(matrixTemp, jMatrix);
        }
    }else{
        if(iMatrix + 1 > matrixTemp->linhas){
            resizeRows(matrixTemp, iMatrix + 1);
        }
    }

    if(!flagErro){
        // cout << "[" << iMatrix << "][" << jMatrix - 1 << "]: " << number << std::endl;
        matrixTemp->matriz[iMatrix][jMatrix - 1] = number;
    }
}

void DCMat::addRowMatrix()
{
    if(flagErro){
        return;
    }

    iMatrix++;
    jMatrix = 0;
    // cout << "\nlin[" << iMatrix << "][" << jMatrix << "]" << std::endl;

    // cout << "Tamanho: " << matrixTemp->linhas << "x" << matrixTemp->colunas << std::endl;
    if(iMatrix > matrixTemp->linhas){
        resizeRows(matrixTemp, iMatrix);
    }
}

void DCMat::addMatrix()
{
    if(flagErro){
        flagErro = false;
        return;
    }

    if(matrix != nullptr){
        delete matrix;
    }
    matrix = matrixTemp;

    matrixTemp = createMatrix();
    // cout << "Matrix adicionada\n";
}

void DCMat::luDecomposition()
{
    if(matrix == nullptr){
        showError(Erro::NoMatrix);
    }else{
        int tamanho = matrix->linhas;

        // Inicializa L U e preenche com zeros
        resizeColumns(&matrixL, tamanho);
        resizeRows(&matrixL, tamanho);
        resizeColumns(&matrixU, tamanho);
        resizeRows(&matrixU, tamanho);

        for(int i = 0; i < tamanho; i++){
            // Construir elementos de U
            for(int j = i; j < tamanho; j++){
                double soma = 0.0;

                for(int k = 0; k < i; k++){
                    soma += matrixL.matriz[i][k] * matrixU.matriz[k][j];
                }
                matrixU.matriz[i][j] = matrix->matriz[i][j] - soma;
            }

            // Construir elementos de L
            for(int j = i; j < tamanho; j++){
                if(i == j){
                    // Diagonal principal de L é 1
                    matrixL.matriz[i][i] = 1.0;
                }else{
                    double soma = 0.0;

                    for(int k = 0; k < i; k++){
                        soma += matrixL.matriz[j][k] * matrixU.matriz[k][i];
                    }

                    if(matrixU.matriz[i][i] == 0){
                        matrixL.matriz[j][i] = 0;
                    }else{
                        matrixL.matriz[j][i] = (matrix->matriz[j][i] - soma) / matrixU.matriz[i][i];
                    }
                }
            }
        }

        // showMatrix(&matrixL);
        // cout << "\nMatriz L\n";
        // showMatrix(&matrixU);
        // cout << "\nMatriz U\n";
    }
}

double DCMat::calculateDeterminant()
{
    // det(A) = det(L) * det(U)
    // det(L) = 1
    double determinante = 1.0;

    luDecomposition();
    for(int i = 0; i < matrixU.linhas; i++){
        determinante *= matrixU.matriz[i][i];
    }

    return determinante;
}

void DCMat::solveDeterminant()
{
    if(matrix == nullptr){
        showError(Erro::NoMatrix);
    }else{
        // Verifica se é quadrada
        if(matrix->colunas != matrix->linhas){
            showError(Erro::MatrixFormat);
        }else{
            showValue(calculateDeterminant());
        }
    }
}

void DCMat::solveLinearSystem()
{
    if(matrix == nullptr){
        showError(Erro::NoMatrix);
    }else{
        // Verifica se é uma matriz n x (n + 1)
        if(matrix->colunas != matrix->linhas + 1){
            showError(Erro::MatrixFormat);
        }else{
            int n = matrix->linhas;

            // A * x = b
            // A = L * U
            double determinante = calculateDeterminant();
            // cout << "\nDeterminante: " << determinante << "\n\n";
            
            // Inicializa b
            vector<double> b(n, 0.0);
            for(int i = 0; i < n; i++){
                b[i] = matrix->matriz[i][n];
                // cout << "b[" << i << "]: " << b[i] << std::endl;
            }
            // cout << "\n";

            // L * y = b
            vector<double> y(n, 0.0);
            for (int i = 0; i < n; i++) {
                double soma = 0.0;

                for (int j = 0; j < i; j++) {
                    soma += matrixL.matriz[i][j] * y[j];
                }
                y[i] = b[i] - soma;
                // cout << "y[" << i << "]: " << y[i] << std::endl;
            }
            // cout << "\n";

            bool impossivel = false;

            // U * x = y
            vector<double> x(n, 0.0);
            for (int i = n - 1; i >= 0; i--) {
                double soma = 0.0;

                for (int j = i + 1; j < n; j++) {
                    soma += matrixU.matriz[i][j] * x[j];
                }

                if(matrixU.matriz[i][i] == 0){
                    if(y[i] - soma != 0){
                        impossivel = true;
                    }
                    x[i] = 0.0;
                }else{
                    x[i] = (y[i] - soma) / matrixU.matriz[i][i];
                }
                // cout << "x[" << i << "]: " << x[i] << std::endl;
            }
            
            // Analisa o determinante
            if(determinante == 0){
                if(impossivel){
                    cout << "\nSI - The Linear System has no solution";
                }else{
                    cout << "\nSPI - The Linear System has infinitely many solutions";
                }
            }else{
                // Mostra o resultado
                cout << "\nMatrix x:\n";

                for(int i = 0; i < n; i++){
                    showValue(x[i]);
                }
            }
        }
    }
}

/******************************************************
*       VARIÁVEIS E DECLARAÇÕES
*******************************************************/

void DCMat::showAllSymbols()
{
    for(const auto& simbolo : symbols){
        cout << "\n";

        cout << simbolo.first << " - ";

        if(simbolo.second.tipo == Tipo::FLOAT){
            cout << "FLOAT";
        }else{
            cout << "MATRIX [" << simbolo.second.matriz->linhas << "]";
            
            if((simbolo.second.matriz->linhas == 1 && simbolo.second.matriz->colunas > 1)
                || (simbolo.second.matriz->linhas != 1)){
                cout << "[" << simbolo.second.matriz->colunas << "]";
            }
        }
    }

    if(symbols.size() > 0)
    {
        cout << "\n\n";
    }
}

void DCMat::showSymbol(string name)
{
    if(symbolExists(name)){
        if(symbols[name].tipo == Tipo::MATRIX){
            showMatrix(symbols[name].matriz);
        }else{
            cout << "\n" << name << " = " << fixed << std::setprecision(float_precision) << symbols[name].valor;
        }      
    }else{
        showError(Erro::UndefinedSymbol);
    }
}

double DCMat::getSymbol(string name)
{
    if(symbolExists(name)){
        return symbols[name].valor;
    }else{
        cout << "\nUndefined symbol [" << name << "]";
        flagUndefined = true;
        return 0;
    }
}

void DCMat::addSymbol(string name, Tipo type, double value)
{
    if(!flagErro){
        if(symbolExists(name))
        {
            if(symbols[name].matriz != nullptr){
                delete symbols[name].matriz;
            }
        }

        if(type == Tipo::FLOAT){
            symbols[name] = {type, value, nullptr};

            showValue(value);
        }
        else if(type == Tipo::MATRIX){
            Matriz *novaMatriz = matrixTemp;
            matrixTemp = createMatrix();

            symbols[name] = {type, 0, novaMatriz};

            showMatrix(symbols[name].matriz);
            cout << "\n\n";
        }
    }
    flagErro = false;
}

bool DCMat::symbolExists(string name)
{
    return symbols.find(name) != symbols.end();
}

bool DCMat::isXVariablePresent(NodeArvore *root)
{
    return findElement(root, TipoElemento::VARIAVEL_X);
}