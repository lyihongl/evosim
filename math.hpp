#pragma once
#include <cmath>
#include <iostream>
#include <Eigen/Dense>


namespace evo_math{

const int RESOLUTION = 720;

double SIN_TABLE[RESOLUTION];
/*
double fast_sigmoid(double x){
    return x/(1+std::abs(x));
}

Eigen::MatrixXd& mat_fast_sigmoid(Eigen::MatrixXd& a){
    return;
}
*/

void init_trig_table(){
    for(int i = 0; i<RESOLUTION; i++){
        SIN_TABLE[i] = std::sin((double)i/((double)RESOLUTION/360)*M_PI/180);
    }
}

double sin(int i){
    return SIN_TABLE[i];
}

double cos(int i){
    i = (i+90*(RESOLUTION/360))%RESOLUTION;
    return SIN_TABLE[i];
}

};