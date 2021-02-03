#pragma once
#include <cmath>
#include <iostream>
#include <Eigen/Dense>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

namespace evo_math
{

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

    void init_trig_table()
    {
        for (int i = 0; i < RESOLUTION; i++)
        {
            SIN_TABLE[i] = std::sin((double)i / ((double)RESOLUTION / 360) * M_PI / 180);
        }
    }

    double sin(int i)
    {
        return SIN_TABLE[i % RESOLUTION];
    }

    double cos(int i)
    {
        i = (i + 90 * (RESOLUTION / 360)) % RESOLUTION;
        return SIN_TABLE[i];
    }

    int normalize_angle(double angle)
    {
        return std::round(angle * RESOLUTION / 360);
    }

    void populate_line_points(std::vector<sf::Vector2f> &list, std::size_t points, sf::Vector2f &start, const double length, const int angle)
    {
        for (int i = 0; i < points + 1; i++)
        {
            list.push_back(sf::Vector2f(start.x + i / (double)points * length * evo_math::cos(normalize_angle(angle)), start.y + i / (double)points * length * evo_math::sin(normalize_angle(angle))));
        }
    }

}; // namespace evo_math