#pragma once
#include "agent_manager.hpp"
#include "logging.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>
#include <vector>

class actions {
public:
  double v_x, v_y, theta;
  actions(double v_x, double v_y, double theta) {
    this->v_x = v_x;
    this->v_y = v_y;
    this->theta = theta;
  }
};

double sigmoid(double x) { return (double)1 / ((double)1 + std::exp(-x)); }

std::unique_ptr<actions>
calculate_action(const std::vector<Eigen::MatrixXd> &weights) {
  Eigen::MatrixXd result = weights[0].unaryExpr(&sigmoid);
  // std::cout<<weights.back()<<std::endl;
  if (weights.back().cols() != 3) {
    log_err(
        "weights matrix final matrix column dimension wrong, expected 2 got: "
        << weights.end()->cols());
  }
  for (int i = 1; i < weights.size(); i++) {
    result *= weights[i];
    result = result.unaryExpr(&sigmoid);
  }
  // std::cout << "RESULT: "<<result<<std::endl;
  return std::unique_ptr<actions>(
      new actions{result(0, 0), result(0, 1), result(0, 2)});
}

// class matrix_layer{
//    float **data;
//    sf::Vector2u dim;
//    matrix_layer();
//};

// matrix_layer::matrix_layer():
// data{nullptr},
// dim{0, 0}{ }

// void calculate_action(actions& output, const std::vector<matrix_layer>
// &weights, const std::vector<matrix_layer> &bias); void* multi(void* arg);

// void calculate_action(actions& output, const std::vector<matrix_layer>
// &weights, const std::vector<matrix_layer> &ias){ pthread_t
// workers[mat_threads]; int cores[mat_threads]; for(int i = 0; i<mat_threads;
// i++){
//    cores[i] = i;
//    pthread_create(&workers[i], NULL, multi, &cores[i]);
//}
//}

// void* multi(void* arg){
//
//    return nullptr;
//}