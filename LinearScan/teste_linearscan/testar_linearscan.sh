#!/bin/bash

try_count=4

function Warning
{
    echo -e "\n\n"
    echo -e "\e[43m                         \e[43m                             \e[49m"
    echo -e "\e[43m          \e[40m \e[43m\e[25m              \e[43m                             \e[49m"
    echo -e "\e[43m         \e[40m \e[43m \e[40m \e[43m\e[25m             \e[43m                             \e[49m"
    echo -e "\e[43m        \e[40m \e[43m  \e[43m \e[40m \e[43m\e[25m            \e[43m \e[40m     \e[43m \e[40m \e[43m   \e[40m \e[43m \e[40m   \e[43m \e[40m     \e[43m \e[40m     \e[43m \e[49m"
    echo -e "\e[43m       \e[40m \e[43m  \e[40m \e[43m  \e[40m \e[43m\e[43m\e[25m           \e[43m \e[40m \e[43m   \e[40m \e[43m \e[40m \e[43m   \e[40m \e[43m  \e[40m \e[43m  \e[40m \e[43m     \e[40m \e[43m   \e[40m \e[43m \e[49m"
    echo -e "\e[43m      \e[40m \e[43m   \e[40m \e[43m   \e[40m \e[43m\e[43m\e[25m          \e[43m \e[40m     \e[43m  \e[40m \e[43m \e[40m \e[43m   \e[40m \e[43m  \e[40m     \e[43m \e[40m \e[43m   \e[40m \e[43m \e[49m"
    echo -e "\e[43m     \e[40m \e[43m    \e[40m \e[43m    \e[40m \e[43m\e[43m\e[25m         \e[43m \e[40m \e[43m   \e[40m \e[43m  \e[40m \e[43m \e[40m \e[43m   \e[40m \e[43m      \e[40m \e[43m \e[40m \e[43m   \e[40m \e[43m \e[49m"
    echo -e "\e[43m    \e[40m \e[43m           \e[40m \e[43m\e[25m        \e[43m \e[40m \e[43m   \e[40m \e[43m   \e[40m \e[43m   \e[40m   \e[43m \e[40m     \e[43m \e[40m     \e[43m \e[49m"
    echo -e "\e[43m   \e[40m \e[43m      \e[40m \e[43m      \e[40m \e[43m\e[43m\e[25m       \e[43m                             \e[49m"
    echo -e "\e[43m  \e[40m \e[43m               \e[40m \e[43m\e[25m      \e[43m                             \e[49m"
    echo -e "\e[43m \e[40m                   \e[43m\e[25m     \e[43m                             \e[49m"
    echo -e "\e[43m                         \e[43m                             \e[49m"
}

function DrawSkull
{
    echo -e "\n\n"
    echo -e "                 \e[41m       \e[49m"
    echo -e "             \e[41m               \e[49m"
    echo -e "          \e[41m                     \e[49m"
    echo -e "         \e[41m                       \e[49m"
    echo -e "        \e[41m                         \e[49m"
    echo -e "       \e[41m                           \e[49m"
    echo -e "       \e[41m                           \e[49m"
    echo -e "       \e[41m        \e[49m   \e[41m     \e[49m   \e[41m        \e[49m"
    echo -e "       \e[41m      \e[49m      \e[41m   \e[49m       \e[41m     \e[49m"
    echo -e "        \e[41m    \e[49m       \e[41m   \e[49m       \e[41m    \e[49m"
    echo -e "        \e[41m    \e[49m      \e[41m     \e[49m      \e[41m    \e[49m"
    echo -e "         \e[41m          \e[49m   \e[41m          \e[49m"
    echo -e "          \e[41m         \e[49m   \e[41m         \e[49m"
    echo -e "            \e[41m                 \e[49m"
    echo -e "             \e[41m               \e[49m"
    echo -e "  \e[41m   \e[49m        \e[41m    \e[49m \e[41m \e[49m \e[41m \e[49m \e[41m \e[49m \e[41m    \e[49m       \e[41m   \e[49m"
    echo -e " \e[41m     \e[49m        \e[41m             \e[49m       \e[41m     \e[49m"
    echo -e "  \e[41m       \e[49m      \e[41m           \e[49m     \e[41m        \e[49m"
    echo -e "\e[41m              \e[49m    \e[41m     \e[49m    \e[41m              \e[49m"
    echo -e "\e[41m                    \e[49m   \e[41m                  \e[49m"
    echo -e " \e[41m   \e[49m      \e[41m               \e[49m \e[41m      \e[49m"
    echo -e "           \e[41m    \e[49m \e[41m               \e[49m"
    echo -e "  \e[41m                  \e[49m \e[41m                   \e[49m"
    echo -e "  \e[41m              \e[49m           \e[41m              \e[49m"
    echo -e "   \e[41m       \e[49m                      \e[41m        \e[49m"
    echo -e "     \e[41m    \e[49m                         \e[41m     \e[49m"
}

function EndTests
{
    echo -e "\n\n"
    echo -e "       \e[41m                      \e[49m"
    echo -e "      \e[41m \e[107m                      \e[41m \e[49m"
    echo -e "     \e[41m \e[107m  \e[41m                    \e[107m  \e[41m \e[49m"
    echo -e "    \e[41m \e[107m  \e[41m                      \e[107m  \e[41m \e[49m"
    echo -e "   \e[41m \e[107m  \e[41m                        \e[107m  \e[41m \e[49m"
    echo -e "  \e[41m \e[107m  \e[41m                          \e[107m  \e[41m \e[49m"
    echo -e " \e[41m \e[107m  \e[41m                            \e[107m  \e[41m \e[49m"
    echo -e " \e[41m \e[107m  \e[41m\e[97m     Processo de testes     \e[107m  \e[41m \e[49m"
    echo -e " \e[41m \e[107m  \e[41m\e[97m         finalizado!        \e[107m  \e[41m \e[49m"
    echo -e " \e[41m \e[107m  \e[41m                            \e[107m  \e[41m \e[49m"
    echo -e " \e[41m \e[107m  \e[41m                            \e[107m  \e[41m \e[49m"
    echo -e " \e[41m \e[107m  \e[41m\e[97m         Bye, bye...        \e[107m  \e[41m \e[49m"
    echo -e " \e[41m \e[107m  \e[41m\e[97m     The cake is a lie!     \e[107m  \e[41m \e[49m"
    echo -e " \e[41m \e[107m  \e[41m                            \e[107m  \e[41m \e[49m"
    echo -e "  \e[41m \e[107m  \e[41m                          \e[107m  \e[41m \e[49m"
    echo -e "   \e[41m \e[107m  \e[41m                        \e[107m  \e[41m \e[49m"
    echo -e "    \e[41m \e[107m  \e[41m                      \e[107m  \e[41m \e[49m"
    echo -e "     \e[41m \e[107m  \e[41m                    \e[107m  \e[41m \e[49m"
    echo -e "      \e[41m \e[107m                      \e[41m \e[49m"
    echo -e "       \e[41m                      \e[49m"
}

function DrawTrophy
{
    echo -e "\n\n"
    echo -e "\e[49m                          "
    echo -e " \e[30;48;5;11m    \e[49m  \e[30;48;5;11m            \e[49m  \e[30;48;5;11m    \e[49m\e[39m "
    echo -e " \e[30;48;5;11m \e[49m  \e[30;48;5;11m \e[49m  \e[30;48;5;11m            \e[49m  \e[30;48;5;11m \e[49m  \e[30;48;5;11m \e[49m\e[39m "
    echo -e " \e[30;48;5;11m \e[49m  \e[30;48;5;11m  \e[49m \e[30;48;5;11m     \e[43m  \e[30;48;5;11m     \e[49m \e[30;48;5;11m  \e[49m  \e[30;48;5;11m \e[49m\e[39m "
    echo -e " \e[30;48;5;11m \e[49m   \e[30;48;5;11m      \e[43m   \e[30;48;5;11m       \e[49m   \e[30;48;5;11m \e[49m\e[39m "
    echo -e " \e[30;48;5;11m \e[49m     \e[30;48;5;11m   \e[43m    \e[30;48;5;11m     \e[49m     \e[30;48;5;11m \e[49m\e[39m "
    echo -e " \e[30;48;5;11m  \e[49m    \e[30;48;5;11m     \e[43m  \e[30;48;5;11m     \e[49m    \e[30;48;5;11m  \e[49m\e[39m "
    echo -e "  \e[30;48;5;11m \e[49m    \e[30;48;5;11m     \e[43m  \e[30;48;5;11m     \e[49m    \e[30;48;5;11m \e[49m\e[39m  "
    echo -e "  \e[30;48;5;11m  \e[49m   \e[30;48;5;11m     \e[43m  \e[30;48;5;11m     \e[49m   \e[30;48;5;11m  \e[49m\e[39m  "
    echo -e "   \e[30;48;5;11m   \e[49m \e[30;48;5;11m     \e[43m  \e[30;48;5;11m     \e[49m \e[30;48;5;11m   \e[49m\e[39m   "
    echo -e "     \e[30;48;5;11m     \e[43m      \e[30;48;5;11m     \e[49m\e[39m     "
    echo -ne "       \e[30;48;5;11m            \e[49m\e[39m       "
    echo -e "      Parabens!!!"
    echo -ne "        \e[30;48;5;11m          \e[49m\e[39m        "
    echo -e "      Voce Acertou Todos os Testes!!!"
    echo -e "         \e[30;48;5;11m        \e[49m\e[39m         "
    echo -e "          \e[30;48;5;11m      \e[49m\e[39m          "
    echo -e "           \e[30;48;5;11m    \e[49m\e[39m           "
    echo -e "            \e[30;48;5;11m  \e[49m\e[39m            "
    echo -e "            \e[30;48;5;11m  \e[49m\e[39m            "
    echo -e "            \e[30;48;5;11m  \e[49m\e[39m            "
    echo -e "           \e[30;48;5;11m    \e[49m\e[39m           "
    echo -e "          \e[30;48;5;11m      \e[49m\e[39m          "
    echo -e "        \e[30;48;5;11m          \e[49m\e[39m        "
    echo -e "       \e[30;48;5;11m            \e[49m\e[39m       "
    echo -e "    \e[30;48;5;136m                  \e[49m\e[39m    "
    echo -e "    \e[30;48;5;136m  \e[43m              \e[30;48;5;136m  \e[49m\e[39m    "
    echo -e " \e[30;48;5;136m     \e[43m              \e[30;48;5;136m     \e[49m\e[39m "
    echo -e " \e[30;48;5;136m                        \e[49m\e[39m "
}

function DrawError
{
    echo -e "\n\n"
    echo -e "    \e[41m       \e[49m\e[39m"
    echo -e "   \e[41m         \e[49m\e[39m"
    echo -e "  \e[41m  \e[107m  \e[41m   \e[107m  \e[41m  \e[49m\e[39m"
    echo -e " \e[41m    \e[107m  \e[41m \e[107m  \e[41m    \e[49m\e[39m"
    echo -ne " \e[41m     \e[107m   \e[41m     \e[49m\e[39m"
    echo -e "       NENHUM TESTE CORRETO!!!"
    echo -e " \e[41m    \e[107m  \e[41m \e[107m  \e[41m    \e[49m\e[39m"
    echo -e "  \e[41m  \e[107m  \e[41m   \e[107m  \e[41m  \e[49m\e[39m"
    echo -e "   \e[41m         \e[49m\e[39m"
    echo -e "    \e[41m       \e[49m\e[39m"
}

function MenuFail
{
    let try_count=try_count-1
    if [ $try_count -gt 1  ];
    then
        echo -e "\n"
        echo -e "###       Resposta Incorreta!       ###"
        echo -e "###  Você possui mais \e[91m$try_count\e[39m tentativas! ###"
        echo -e "### Por favor, responda \e[92mSIM\e[39m ou \e[91mNAO\e[39m. ###\n"
    fi
    
    if [ $try_count == 1 ];
    then
        Warning
        echo -e "\n+-----------------------------------------------------------------+"
        echo -e "|                  Essa é a sua \e[91multima\e[39m tentativa!                 |"
        echo -e "| Por favor, responda \e[92mSIM\e[39m ou \e[91mNAO\e[39m ou este script sera EXTERMINADO. |"
        echo -e "+-----------------------------------------------------------------+\n"
    fi
    
    if [ $try_count == 0 ];
    then
        DrawSkull
        echo -e "\nI'll be back...\n"
        exit;
    fi    
}


corretos=0
failed=0
erro=0
continuar=0
executavel="";

clear
Warning
echo -e "\n"
echo -e "Para que o processo de compilacao e testes do alocador de"
echo -e "registradores seja possivel, eh necessario que as seguintes"
echo -e "ferramentas estejam instaladas no seu computador:"
echo -e "\n"
echo -e "flex \e[93m[somente se voce a utilizou]\e[39m"
echo -e "bison \e[93m[somente se voce a utilizou]\e[39m"
echo -e "gcc"
echo -e "g++"
echo -e "make"
echo -e "diff"
echo -e "unzip"
echo -e "\n"
echo -e "Se uma dessas ferramentas nao estiver presente, o processo"
echo -e "de compilacao e teste nao sera possivel. Tenha certeza de"
echo -e "que as mesmas estao instaladas no seu computador, pois este"
echo -e "script nao verifica a existencia das mesmas."
echo -e "\n"

while [ $continuar == 0 ]; do
    read -p "Voce deseja continuar? [Sim/Nao] " yn
    case $yn in
        [Ss][Ii][Mm] ) continuar=1; break;;
        [Nn][Aa][Oo] ) EndTests; exit;;
        * ) MenuFail;;
    esac
done

echo -e "\n\n"
echo -e "+----------------------------------------------------------+"
echo -e "|                                                          |"
echo -e "| Iniciando Processo de Teste do Alocador de Registradores |"
echo -e "|                                                          |"
echo -e "+----------------------------------------------------------+\n"    

rm -Rf ./safe_box/*
rm -Rf ./saidas/*

mkdir diferencas
mkdir saidas
mkdir safe_box

echo -e "Procurando arquivo linearscan.zip... \c"
if [ ! -e ./linearscan.zip ];
then
    DrawSkull
    echo -e "\n\nERRO: Arquivo linearscan.zip ***NAO*** encontrado!!!\n\n"
    exit
else
    echo -e "\e[92mOK\e[39m"    
fi

echo "Copiando arquivos..."
cp ./linearscan.zip ./safe_box/
if [ ! -e ./safe_box/linearscan.zip ];
then
    DrawSkull
    echo "Erro ao copiar arquivo linearscan.zip para pasta safe_box!!!"
    exit
fi
echo "Descompactando..."
unzip -j -o -q ./safe_box/linearscan.zip -d ./safe_box/

echo -e "Procurando Makefile... \c"
if [ ! -e ./safe_box/Makefile ];
then
    DrawSkull
    echo -e "\n\nERRO: Makefile ***NAO*** encontrado!!!\n\n"
    exit
else
    echo -e "\e[92mOK\e[39m"    
fi
echo -e "Compilando...\n\n"
make -C ./safe_box -I ./safe_box

if [ $erro == 0 ];
then
    if [ ! -e ./safe_box/linearscan.exe ]; then
        if [ ! -e ./safe_box/linearscan ]; then
           DrawSkull
           echo -e "\n\nErro de compilacao ou Executavel nao encontrado.\n\n"
           let erro=1
        else
           executavel="linearscan"
        fi
    else
       executavel="linearscan.exe"
    fi
fi

if [ $erro == 0 ];
then
    let corretos=0
    let failed=0
    
    echo -e "\n\nRealizando Testes..."
    for i in $(ls ./testes/*.txt)
    do
        echo $i > linha.txt
        name=$(cut -d"/" -f3 linha.txt) 
        echo -ne "   Teste: \e[93m$name\e[39m"
        ./safe_box/$executavel < $i > ./saidas/saida_$name
        diff ./saidas/saida_$name ./saidas_padrao/"saida_"$name > ./diferencas/"diff_"$name
        rc=$?;
        if [ $rc == 0 ]; 
        then 
            echo -e " -> \e[92mOK\e[39m"
            let corretos=corretos+1
        fi
        if [ $rc == 1 ];
        then
            echo -e " -> \e[91mFail\e[39m"
            let failed=failed+1
        fi
        if [ $rc == 2 ];
        then
            echo -e " -> \e[91mUnexpected Problem.\e[39m"
            let failed=failed+1
        fi
    done
    echo -e "\n"
    echo -e "Corretos: \e[92m$corretos\e[39m"
    echo -e "Incorretos \e[91m$failed\e[39m"
    
    if [ $corretos == 22 ];
    then
        DrawTrophy
    fi
    
    if [ $corretos == 0 ];
    then
        DrawError
    fi
    

fi

echo -e "\nApagando arquivos temporarios...\n"
rm -Rf ./safe_box/*
rm -Rf linha.txt
rm -f ./*stackdump*
# Pode deixar comentado caso queira ver as diferenças de cada teste
rm -Rf ./saidas/*
rm -Rf ./diferencas/*

let erro=0