#include <vector>
#include "math2d.hpp"
#include "error_handling.hpp"

enum agent_type{
    pred, prey
};

class agent_manager{
    public:
        agent_manager(){};
        std::vector<position> positions;
        std::vector<agent_type> types;
        std::vector<decision_matrix> decision_matrices;
        std::size_t add_agent(position& p, agent_type& t, decision_matrix& m);
        std::size_t num_agents;

        template<typename T>
        status get_val(T* ret_val, std::size_t i);

};

std::size_t agent_manager::add_agent(position& p, agent_type& t, decision_matrix& m){
    positions.push_back(p);
    types.push_back(t);
    decision_matrices.push_back(m);
    return num_agents++;
}

template<typename T>
status agent_manager::get_val(T* ret_val, std::size_t i){
    if(i > num_agents){
        return array_index;
    }
    if(std::is_same<T, position>::value){
        ret_val = &positions[i];
    } else if (std::is_same<T, agent_type>::value){
        ret_val = &types[i];
    } else if (std::is_same<T, decision_matrix>::value){
        ret_val = &types[i];
    }
}
