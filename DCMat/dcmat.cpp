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
}

// Desconstrutor
DCMat::~DCMat()
{
}

void DCMat::setHView(double low, double high)
{
    if(low >= high){
        showError("h_view_lo must be smaller than h_view_hi");
        // cout << low << high;
    }else{
        h_view.high = high;
        h_view.low = low;
    }
}

void DCMat::setVView(double low, double high)
{
    if(low >= high){
        showError("v_view_lo must be smaller than v_view_hi");
        // cout << low << high;
    }else{
        v_view.high = high;
        v_view.low = low;
    }
}

/******************************************************
*       CONFIGURAÇÕES
*******************************************************/

void DCMat::showError(string message)
{
    cout << "\nERROR: " << message << "\n\n";
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
    cout << "\nConnect Dots: " << (connect_dots ? "ON" : "OFF") << "\n" << endl;
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