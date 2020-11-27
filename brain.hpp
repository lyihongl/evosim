#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <pthread.h>

#define mat_threads 4

typedef struct actions{
    float v_x, v_y;
} actions;

class matrix_layer{
    float **data;
    sf::Vector2u dim;
    matrix_layer();
};

matrix_layer::matrix_layer():
data{nullptr}, 
dim{0, 0}{ }

void calculate_action(actions& output, const std::vector<matrix_layer> &weights, const std::vector<matrix_layer> &bias);
void* multi(void* arg);


void calculate_action(actions& output, const std::vector<matrix_layer> &weights, const std::vector<matrix_layer> &ias){
    pthread_t workers[mat_threads];
    int cores[mat_threads];
    for(int i = 0; i<mat_threads; i++){
        cores[i] = i;
        pthread_create(&workers[i], NULL, multi, &cores[i]);
    }
}

void* multi(void* arg){

    return nullptr;
}