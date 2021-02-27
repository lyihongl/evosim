#pragma once
#include <SFML/System/Vector2.hpp>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <vector>

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

float abs_dist(sf::Vector2f vec) {
    return std::sqrt((float)(vec.x * vec.x + vec.y * vec.y));
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
    //log("populate line points angle: "<<angle);
    for (int i = 0; i < points + 1; i++) {
        list[i] = sf::Vector2f(start.x + i / (double)points * length * evo_math::cos(angle), start.y + i / (double)points * length * evo_math::sin(angle));
    }
}

bool angle_between(float langle, float rangle, float comp) {
    return fmod(langle - rangle, 360) >= fmod(langle-comp, 360);
}

template <typename T>
void print_vector(const char* name, const std::vector<T> &v) {
  std::cout<<name<<":"<<std::endl;
  for(size_t i=0; i<v.size(); i++) {
    std::cout<<i<<":"<<std::endl;
    std::cout<<v[i]<<std::endl;
  }
}

template <typename T>
void print(const char* name, const T &t) {
  std::cout<<name<<":"<<std::endl;
  std::cout<<t<<std::endl;
}

void start_scan_positions(std::vector<sf::Vector2f> &start_scan, std::vector<int> &scan_angles, float angle){
    float angles[]{0, M_PI / 4.f, M_PI / 2.f, 3 * M_PI / 4.f, M_PI, 5 * M_PI / 4.f, 3 * M_PI / 2.f, 7 * M_PI / 4.f};

    float x = 12, y = 0;
    for (int i = 0; i < 8; i++) {
        scan_angles[i] = (int)(std::round(angle + angles[i]*180/M_PI))%360;
        angles[i]+=(angle*M_PI/180);
        //log("angles: " << angles[i]);
        start_scan[i] = sf::Vector2f{(std::abs(x * std::cos(angles[i])) > 1e-05) ? x * std::cos(angles[i]) : 0,
                              (std::abs(x * std::sin(angles[i])) > 1e-05) ? x * std::sin(angles[i]) : 0};
        //log(start_scan[i].x << " " << start_scan[i].y);
    }
}

};  // namespace evo_math