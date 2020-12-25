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
        agent_manager() : num_agents{0} {};
        std::vector<sf::Vector2f> positions;
        std::vector<double> angles;
        std::vector<agent_type> types;
        std::vector<std::vector<Eigen::MatrixXd>> decision_matrices;
        std::size_t add_agent(sf::Vector2f& p, agent_type& t, double angle=0);
        std::size_t add_agent(sf::Vector2f&& p, agent_type&& t, double angle=0);
        std::size_t add_decision_matrix(std::size_t agent, Eigen::MatrixXd& m);
        std::size_t num_agents;

};

std::size_t agent_manager::add_agent(sf::Vector2f& p, agent_type& t, double angle){
    positions.push_back(p);
    types.push_back(t);
    angles.push_back(angle);
    decision_matrices.push_back(std::vector<Eigen::MatrixXd>());
    return num_agents++;
}
std::size_t agent_manager::add_agent(sf::Vector2f&& p, agent_type&& t, double angle){
    positions.push_back(p);
    types.push_back(t);
    decision_matrices.push_back(std::vector<Eigen::MatrixXd>());
    //types.push_back(t);
    angles.push_back(angle);
    return num_agents++;
}
std::size_t agent_manager::add_decision_matrix(std::size_t agent, Eigen::MatrixXd& m){
    decision_matrices[agent].push_back(m);
    return decision_matrices[agent].size();
}