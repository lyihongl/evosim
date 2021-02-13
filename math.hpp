#pragma once
#include <Eigen/Dense>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

/*
Caches trig values in an array
To access with integer, certain int resolution is used, ie: f: int -> int, resolution -> 360 (resolution uniformly mapped to a value between 0 and 360)
All functions designed to take value between 0 and 360, which the function will then normalize to our resolution for use in the cached array
*/

namespace evo_math {

enum angle_comp { in,
                  cwof,
                  ccwof };

const int RESOLUTION = 360 * 8;

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

float abs_dist(double a, double b) {
    return std::sqrt((float)(a * a + b * b));
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

bool angle_between(float langle, float rangle, float comp) {
    return fmod(langle - rangle, 360) >= fmod(langle-comp, 360);
}

};  // namespace evo_math