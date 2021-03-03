#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <unordered_set>
#include <stack>
#include <set>
#include <utility>
#include <algorithm>
//#include "math2d.hpp"
#include <Eigen/Dense>
#include <unordered_map>
#include "MLP.hpp"
#include "error_handling.hpp"

enum agent_type{
    pred, prey
};

class agent_manager{
    public:
        agent_manager() : num_agents{0} {};
        std::vector<sf::Vector2f> positions;
        std::vector<double> angles;
        std::vector<double> fovs;
        std::vector<sf::Color> colors;
        std::vector<uint8_t> eye_input_r;
        std::vector<uint8_t> eye_input_b;
        std::vector<uint8_t> eye_input_g;
        std::vector<double> input_dist;
        std::vector<float> energy;
        std::unordered_set<std::size_t> active_agent_set;
        //std::set<std::pair<unsigned int, std::size_t>> sorted_agent_set;
        std::stack<std::size_t> empty_slots_stack;
        std::vector<bool> spike;
        std::vector<unsigned int> time_alive;
        std::vector<float> angular_v;
        std::vector<float> velocity;
        //std::vector<std::unordered_map<std::string, double>> actions;
        //std::vector<agent_type> types;
        std::vector<MLP> MLPs;
        //std::vector<std::vector<Eigen::MatrixXd>> decision_matrices;
        void add_agent(sf::Vector2f& p, sf::Color& t, MLP& m, double angle=0, double fov=20);
        void add_agent(sf::Vector2f&& p, sf::Color&& t, MLP&& m, double angle=0, double fov=20);
        void remove_agent(std::size_t i);
        //std::size_t add_MLP(std::size_t agent, MLP& m);
        std::size_t num_agents;

};

void agent_manager::add_agent(sf::Vector2f& p, sf::Color& t, MLP& m, double angle, double fov ){
    if(empty_slots_stack.size() == 0){
        active_agent_set.insert(num_agents);
        positions.push_back(p);
        colors.push_back(t);
        angles.push_back(angle);
        fovs.push_back(fov);
        MLPs.push_back(m);
        eye_input_r.push_back(0);
        eye_input_b.push_back(0);
        eye_input_g.push_back(0);
        energy.push_back(100.f);
        spike.push_back(0);
        time_alive.push_back(0);
        angular_v.push_back(0);
        velocity.push_back(0);
        input_dist.push_back(100000);
        //sorted_agent_set.insert({0, num_agents});
        num_agents++;
    } else {
        std::size_t index = empty_slots_stack.top();
        empty_slots_stack.pop();
        active_agent_set.insert(index);
        positions[index] = p;
        colors[index] = t;
        angles[index] = angle;
        fovs[index] = fov;
        MLPs[index] = m;
        eye_input_r[index] = 0;
        eye_input_b[index] = 0;
        eye_input_g[index] = 0;
        energy[index] = 100.f;
        spike[index] = 0;
        time_alive[index] = 0;
        angular_v[index] = 0;
        velocity[index] = 0;
        input_dist[index] = 100000;
        //sorted_agent_set.begin() -> first = 1;
        //auto it = std::find_if(sorted_agent_set.begin(), sorted_agent_set.end(), [&](const std::pair<unsigned int, std::size_t>& val)-> bool {
        //    return val.second == index;
        //});
        //sorted_agent_set.erase(it);
        //sorted_agent_set.insert({0, num_agents});
        //(*it).first = 0;
        //it -> first = 0;
        //sorted_agent_set[index] = {0, index};
    }
}
void agent_manager::add_agent(sf::Vector2f&& p, sf::Color&& t, MLP&& m, double angle, double fov){
    if(empty_slots_stack.size() == 0){
        active_agent_set.insert(num_agents);
        positions.push_back(p);
        colors.push_back(t);
        angles.push_back(angle);
        fovs.push_back(fov);
        MLPs.push_back(m);
        eye_input_r.push_back(0);
        eye_input_b.push_back(0);
        eye_input_g.push_back(0);
        energy.push_back(100.f);
        spike.push_back(0);
        time_alive.push_back(0);
        angular_v.push_back(0);
        velocity.push_back(0);
        input_dist.push_back(100000);
        //sorted_agent_set.insert({0, num_agents});
        num_agents++;
    } else {
        std::size_t index = empty_slots_stack.top();
        empty_slots_stack.pop();
        active_agent_set.insert(index);
        positions[index] = p;
        colors[index] = t;
        angles[index] = angle;
        fovs[index] = fov;
        MLPs[index] = m;
        eye_input_r[index] = 0;
        eye_input_b[index] = 0;
        eye_input_g[index] = 0;
        energy[index] = 100.f;
        spike[index] = 0;
        time_alive[index] = 0;
        angular_v[index] = 0;
        velocity[index] = 0;
        input_dist[index] = 100000;
    }
}

void agent_manager::remove_agent(std::size_t i){
    if(active_agent_set.find(i) == active_agent_set.end()) return;
    empty_slots_stack.push(i);
    active_agent_set.extract(i);
    //return --num_agents;
}
//std::size_t agent_manager::add_MLP(std::size_t agent, MLP& m){
//    //MLPs[agent].push_back(m);
//    //decision_matrices[agent].push_back(m);
//    //return decision_matrices[agent].size();
//}