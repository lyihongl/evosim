#include <Eigen/Dense>
#include <vector>
#include "logging.hpp"


typedef Eigen::Matrix<double, Eigen::Dynamic, 1> VectorXn;
typedef Eigen::Array <double, Eigen::Dynamic, 1> ArrayXn;

struct mnet{
    Eigen::ArrayXi layers;
    std::vector<Eigen::MatrixXd> weights;
    std::vector<VectorXn> outputs;
    std::vector<VectorXn> inputs;

    mnet(Eigen::ArrayXi layers, double rval);
    ArrayXn eval(ArrayXn input);
};

ArrayXn mnet::eval(ArrayXn input){
    outputs.clear();
    inputs.clear();
    input.conservativeResize(layers[0] + 1);
}