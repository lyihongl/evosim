#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
//#include "math2d.hpp"
#include <Eigen/Dense>
#include "error_handling.hpp"

enum agent_type{
    pred, prey
};

class agent_manager{
    public:
        agent_manager(){};
        std::vector<sf::Vector2f> positions;
        std::vector<agent_type> types;
        std::vector<std::vector<Eigen::MatrixXd>> decision_matrices;
        std::size_t add_agent(sf::Vector2f& p, agent_type& t);
        std::size_t add_agent(sf::Vector2f&& p, agent_type&& t);
        std::size_t add_decision_matrix(std::size_t agent, Eigen::MatrixXd& m);
        std::size_t num_agents;

        template<typename T>
        status get_val(T* ret_val, std::size_t i);

};

std::size_t agent_manager::add_agent(sf::Vector2f& p, agent_type& t){
    positions.push_back(p);
    types.push_back(t);
    decision_matrices.push_back(std::vector<Eigen::MatrixXd>());
    return num_agents++;
}
std::size_t agent_manager::add_agent(sf::Vector2f&& p, agent_type&& t){
    positions.push_back(p);
    types.push_back(t);
    decision_matrices.push_back(std::vector<Eigen::MatrixXd>());
    types.push_back(t);
    return num_agents++;
}
std::size_t agent_manager::add_decision_matrix(std::size_t agent, Eigen::MatrixXd& m){
    decision_matrices[agent].push_back(m);
    return decision_matrices[agent].size();
}

template<typename T>
status agent_manager::get_val(T* ret_val, std::size_t i){
    if(i > num_agents){
        return array_index;
    }
    if(std::is_same<T, sf::Vector2f>::value){
        ret_val = &positions[i];
    } else if (std::is_same<T, agent_type>::value){
        ret_val = &types[i];
    } else if (std::is_same<T, Eigen::MatrixXd>::value){
        ret_val = &types[i];
    }
}
