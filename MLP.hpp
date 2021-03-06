#pragma once
#include <Eigen/Dense>
#include <vector>
#include "logging.hpp"


typedef Eigen::Matrix<double, Eigen::Dynamic, 1> VectorXn;
typedef Eigen::Array <double, Eigen::Dynamic, 1> ArrayXn;

struct MLP{
    Eigen::ArrayXi layers;
    std::vector<Eigen::MatrixXd> weights;
    std::vector<VectorXn> outputs;
    std::vector<VectorXn> inputs;

    MLP (Eigen::ArrayXi layers, double rval);
    MLP (const MLP& m);
    ArrayXn eval(ArrayXn input);
};

MLP::MLP (Eigen::ArrayXi layers, double rval){
    this -> layers = layers;
    for(std::size_t i = 1; i<layers.size(); i++){
        weights.push_back(Eigen::MatrixXd::Random(layers[i], layers[i-1]+1)*rval);
    }
}

MLP::MLP(const MLP& m){
    this -> layers = m.layers;
    this -> weights = m.weights;
}

ArrayXn MLP::eval(ArrayXn input){
    outputs.clear();
    inputs.clear();
    //log("a");
    //log(layers[0]);
    input.conservativeResize(layers[0] + 1);
    //log("a");
    input(layers[0]) = 1;
    //log("a");
    inputs.push_back(input);
    for(int i = 0; i<weights.size(); i++){
        ArrayXn nets = weights[i]*input.matrix();
        ArrayXn activations = 1/(1+(-nets).exp());
        outputs.push_back(activations);
        activations.conservativeResize(layers[i+1]+1);
        activations(layers[i+1]) = 1;
        inputs.push_back(activations);
        input = activations;
    }

    ArrayXn ret = outputs.back();

    return ret;
}