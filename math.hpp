#pragma once
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

namespace evo_math {

const int RESOLUTION = 720 * 4;

double SIN_TABLE[RESOLUTION];
double ARCSIN_TABLE[RESOLUTION];
double ARCCOS_TABLE[RESOLUTION];
/*
double fast_sigmoid(double x){
    return x/(1+std::abs(x));
}

Eigen::MatrixXd& mat_fast_sigmoid(Eigen::MatrixXd& a){
    return;
}
*/

float pythagoras(double a, double b){
    return std::sqrt((float)(a*a+b*b));
}

void init_trig_table() {
    for (int i = 0; i < RESOLUTION; i++) {
        SIN_TABLE[i] = std::sin((double)i / ((double)RESOLUTION / 360) * M_PI / 180);
    }
}

int normalize_angle(double angle) {
    return std::round(angle * RESOLUTION / 360);
}

double sin(const int i) {
    //i = normalize_angle(i);
    if (i < 0) {
        return SIN_TABLE[normalize_angle(i) % RESOLUTION + RESOLUTION];
    } else {
        return SIN_TABLE[normalize_angle(i) % RESOLUTION];
    }
}

double cos(const int i) {
    //i = normalize_angle(i);
    if (normalize_angle(i) + 90 * (RESOLUTION / 360) < 0) {
        return SIN_TABLE[(normalize_angle(i) + 90 * (RESOLUTION / 360)) % RESOLUTION + RESOLUTION];
    } else {
        return SIN_TABLE[(normalize_angle(i) + 90 * (RESOLUTION / 360)) % RESOLUTION];
    }
}

void populate_line_points(std::vector<sf::Vector2f> &list, std::size_t points, sf::Vector2f &start, const double length, const int angle) {
    for (int i = 0; i < points + 1; i++) {
        list.push_back(sf::Vector2f(start.x + i / (double)points * length * evo_math::cos(normalize_angle(angle)), start.y + i / (double)points * length * evo_math::sin(normalize_angle(angle))));
    }
}

bool angle_between(float langle, float rangle, float comp){
    if(normalize_angle(langle) % RESOLUTION > RESOLUTION/2){
        langle = -normalize_angle(langle) % RESOLUTION + RESOLUTION/2;
    }
    if(normalize_angle(rangle) % RESOLUTION > RESOLUTION/2){
        rangle = -normalize_angle(rangle) % RESOLUTION + RESOLUTION/2;
    }
    comp = normalize_angle(comp);
    return (comp <= langle && comp >= rangle);
    //int lquad, rquad;
    //lquad = (int)langle/90+1;
    //rquad = (int)langle/90+1;
    //log("lquad: "<< lquad);
    //std :: cout << lquad << std::
}

};  // namespace evo_math