#pragma once
#include <cmath>
#include <Eigen/Dense>

double fast_sigmoid(double x){
    return x/(1+std::abs(x));
}

Eigen::MatrixXd& mat_fast_sigmoid(Eigen::MatrixXd& a){
    return nullptr;
}


