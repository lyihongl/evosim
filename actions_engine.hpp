#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include "render_engine.hpp"
#include "brain.hpp"
#include "agent_manager.hpp"
#include "error_handling.hpp"
#include "types.hpp"

class actions_engine{
    public:
    actions_engine(){};
    render_engine* p_r_engine;
    std::vector<generic_func> function_list;
    std::vector<void*> function_args;
    agent_manager* p_am;
    status add_function(generic_func_render f, void* a); 
    bool run{false};
    void run_engine();
};

void actions_engine::run_engine(){
    std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end = std::chrono::system_clock::now();
    for(;run;){
        time_now = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> delta = time_now - time_end;

        // limit tickrate to 60/s
        if(delta.count() > 8){

            // calculate actions and add them to position for each agent
            for(int i = 0; i<p_am->num_agents; i++){
                std::unique_ptr<actions> a = std::move(calculate_action(p_am->decision_matrices[i]));
                p_am->positions[i]+=sf::Vector2f(a->v_x/4, a->v_y/4);
            }

            // run passed functions
            auto f_it = function_list.begin();
            auto a_it = function_args.begin();
            for(;f_it!=function_list.end() && a_it != function_args.end(); f_it++, a_it++){
                (*f_it)(p_am, *a_it);
            }
            log(p_r_engine->get_pixel(100, 100));
            time_end = std::chrono::system_clock::now();
        }
    }
}