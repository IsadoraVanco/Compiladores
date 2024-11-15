#include <iostream>
#include <iomanip>
#include "dcmat.h"

using std::cout;
using std::endl;
using std::fixed;

// Construtor
DCMat::DCMat()
{
    resetSettings();
    matrix.resize(maxMatrix, vector<double>(maxMatrix));
    flagErro = false;
}

// Desconstrutor
DCMat::~DCMat()
{
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
        flagErro = true;
        break;
    
    default:
        break;
    }
}

void DCMat::showAbout()
{
    cout << "\n+----------------------------------------------+" << endl;
    cout << "|                                              |" << endl;
    cout << "|              DCMAT - V. 2024.01              |" << endl;
    cout << "|         202200560356 - Isadora Vanço         |" << endl;
    cout << "|                                              |" << endl;
    cout << "+----------------------------------------------+";
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
*       CALCULAR VALORES
*******************************************************/

void DCMat::showValue(double value)
{
    if(!flagErro){
        cout << "\n" << fixed << std::setprecision(float_precision) << value;
    }
    flagErro = false;
}   

/******************************************************
*       VARIÁVEIS E DECLARAÇÕES
*******************************************************/

void DCMat::showMatrix()
{
    if(matrix.empty()){
        cout << "\nNo matrix defined!";
    }else{

    }
}

void DCMat::showSymbol(string name)
{
    if(symbols.find(name) != symbols.end()){
        if(symbols[name].tipo == Tipo::MATRIX){
            showMatrix();
        }else{
            cout << "\n" << name << " = " << fixed << std::setprecision(float_precision) << symbols[name].valor;
        }      
    }else{
        cout << "\nUndefined symbol";
    }
}

void DCMat::showAllSymbols()
{
    for(const auto& simbolo : symbols){
        cout << "\n";

        cout << simbolo.first << " - ";

        if(simbolo.second.tipo == Tipo::FLOAT){
            cout << "FLOAT";
        }else{
            cout << "MATRIX [" << fixed << std::setprecision(0) << simbolo.second.valor << "]";
            
            if(simbolo.second.valor > 1){
                cout << "[" << fixed << std::setprecision(0) << simbolo.second.valor << "]";
            }
        }
    }
}

double DCMat::getSymbol(string name)
{
    if(symbols.find(name) != symbols.end()){
        return symbols[name].valor;
    }else{
        cout << "\nUndefined symbol [" << name << "]";
        flagErro = true;
        return 0;
    }
}

void DCMat::addSymbol(string name, Tipo type, double value)
{
    if(!flagErro){
        symbols[name] = {type, value, NULL};
        showValue(value);
    }
    flagErro = false;
}