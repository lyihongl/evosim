#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

#include "agent_manager.hpp"
#include "brain.hpp"
#include "error_handling.hpp"
#include "math.hpp"
#include "omni.hpp"
#include "types.hpp"

class actions_engine {
   public:
    //render_engine* p_r_engine;
    std::vector<generic_func> function_list;
    std::vector<void *> function_args;
    omni_sight &os;
    //agent_manager* os.am;
    sf::RenderTexture window_texture;
    sf::Image *p_window_image;
    status add_function(generic_func_render f, void *a);
    bool run{false};
    void run_engine();
    actions_engine(omni_sight &os) : os{os} {}
    int tps;
    std::size_t longest_alive_index;
};

void actions_engine::run_engine() {
    std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end_tps = std::chrono::system_clock::now();
    int ticks = 0;
    tps = 0;
    int i = 0;
    bool sec_passed = false;
    unsigned int mutate_max = 0;
    std::size_t mutate_max_index = 0;
    //float omega = 0.15;
    for (; run;) {
        time_now = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> delta_second = time_now - time_end_tps;

        if (delta_second.count() > 1000) {
            tps = ticks;
            ticks = 0;
            time_end_tps = std::chrono::system_clock::now();
            sec_passed = true;
        }

        // limit tickrate to 60/s
        //if(delta.count() > 8){
        ticks++;

        for (int i = 0; i < os.am->num_agents; i++) {
            if (os.am->active_agent_set.find(i) == os.am->active_agent_set.end()) continue;
            os.am->eye_input_b[i] = 0;
            os.am->eye_input_g[i] = 0;
            os.am->eye_input_r[i] = 0;
            if (sec_passed) {
                os.am->time_alive[i] += 1;
            }
            //int seen = 0;
            for (int j = 0; j < os.am->num_agents; j++) {
                if (i != j) {
                    float dist = evo_math::abs_dist(os.am->positions[i] - os.am->positions[j]);
                    if ((dist < AGENT_SIZE && (os.am->spike[i] || os.am->spike[j]))) {
                        os.am->remove_agent(j);
                        os.am->energy[i] = (os.am->energy[i] + 20 <= 100) ? os.am->energy[i] + 20 : 100;
                    }

                    sf::Vector2f pos = os.am->positions[j] - os.am->positions[i];
                    //log( "i: " <<i <<" "<< pos.x << " " << pos.y );
                    float langle = os.am->angles[i] + os.am->fovs[i];
                    float rangle = os.am->angles[i] - os.am->fovs[i];

                    //log(pos.x <<" "<<-pos.y <<" "<<std::atan2(-pos.y, pos.x)*180/M_PI);
                    float atan = std::atan2(-pos.y, pos.x) * 180 / M_PI;
                    //if(atan < 0) atan += 360;
                    float ang_diff = os.am->angles[i] - atan;
                    if (std::abs(ang_diff) > 180) ang_diff = 360 - std::abs(ang_diff);
                    ang_diff = std::abs(ang_diff);

                    if (ang_diff < os.am->fovs[i]) {
                        //seen++;
                        if(dist < os.am->input_dist[i]){
                            os.am->input_dist[i] = dist;
                            os.am->eye_input_b[i] = os.am->colors[j].b / dist;
                            os.am->eye_input_g[i] = os.am->colors[j].g / dist;
                            os.am->eye_input_r[i] = os.am->colors[j].r / dist;
                        }
                        //log(i << " working: " << ang_diff);
                    }
                    //if (i == 0) {
                    //    os.am->positions[i] += {0, -0.5};
                    //}
                }
            }
            ArrayXn input(6);
            input << os.am->eye_input_b[i], os.am->eye_input_g[i], os.am->eye_input_r[i], os.am->angular_v[i], os.am->velocity[i], (int)os.am->spike[i];
            //log("input: " << input);
            ArrayXn res = os.am->MLPs[i].eval(input);
            os.am->angles[i] = fmod(os.am->angles[i] + (res[1]-0.5) * 15, 360);
            os.am->angular_v[i] = (res[1]-0.5)*15;
            os.am->velocity[i] = (res[0]-0.5);


            auto it = std::max_element(os.am->time_alive.begin(), os.am->time_alive.end());
            longest_alive_index = std::distance(os.am->time_alive.begin(), it);

            //if(os.am->time_alive[i]>mutate_max){
            //    mutate_max = os.am -> time_alive[i];
            //    mutate_max_index = i;
            //}

            //if (os.am->eye_input_b[i] != 0 || os.am->eye_input_g[i] != 0 || os.am->eye_input_r[i] != 0) {
            //    log((int)os.am->eye_input_b[i] << " " << (int)os.am->eye_input_g[i] << " " << (int)os.am->eye_input_r[i]);
            //    log("res: " << res[1] << " " << os.am->positions[i].x << " " << os.am->positions[i].y);
            //}
            os.am->energy[i] -= 0.05;
            if (os.am->energy[i] <= 0) {
                os.am->remove_agent(i);
            }
            if (os.am->empty_slots_stack.size() > 0) {
                os.am->add_agent(sf::Vector2f{(std::rand() % 800) + 100, 
                (std::rand() % 800) + 100}, 
                sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255), 
                MLP(os.layers, vary_weights(os.am->MLPs[longest_alive_index].weights, os.layers)), 
                std::rand() % 360);
            }
            os.am->positions[i] += {(res[0]-0.5) * evo_math::cos(os.am->angles[i]), (res[0]-0.5) * evo_math::sin(os.am->angles[i])};

            os.am->spike[i] = (res[2] >= 0.5) ? 1 : 0;
        }
        //longest_alive_index = mutate_max_index;
        sec_passed = (sec_passed) ? false : sec_passed;
        //if(sec_passed) {
        //    sec_passed = false;
        //}
        time_end = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> delta = time_now - time_end;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(8ms - delta);
        //}
    }
}