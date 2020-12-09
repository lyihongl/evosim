#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <Eigen/Dense>
#include "agent_manager.hpp"
#include "logging.hpp"


typedef struct actions{
    float v_x, v_y, theta;
} actions;

void calculate_action(actions& output, const std::vector<Eigen::MatrixXd>& weights){
    Eigen::MatrixXd result = weights[0];
    if(weights.end()->cols() != 3){
        log_err("weights matrix final matrix column dimension wrong, expected 2 got: " << weights.end()->cols());
    }
    for(int i = 1; i<weights.size(); i++){
        result*=weights[i];
    }
}

//class matrix_layer{
//    float **data;
//    sf::Vector2u dim;
//    matrix_layer();
//};

//matrix_layer::matrix_layer():
//data{nullptr}, 
//dim{0, 0}{ }

//void calculate_action(actions& output, const std::vector<matrix_layer> &weights, const std::vector<matrix_layer> &bias);
//void* multi(void* arg);


//void calculate_action(actions& output, const std::vector<matrix_layer> &weights, const std::vector<matrix_layer> &ias){
    //pthread_t workers[mat_threads];
    //int cores[mat_threads];
    //for(int i = 0; i<mat_threads; i++){
    //    cores[i] = i;
    //    pthread_create(&workers[i], NULL, multi, &cores[i]);
    //}
//}

//void* multi(void* arg){
//
//    return nullptr;
//}