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
};

void actions_engine::run_engine() {
    std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end_tps = std::chrono::system_clock::now();
    int ticks = 0;
    tps = 0;
    int i = 0;
    //float omega = 0.15;
    for (; run;) {
        time_now = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> delta_second = time_now - time_end_tps;

        if (delta_second.count() > 1000) {
            tps = ticks;
            ticks = 0;
            time_end_tps = std::chrono::system_clock::now();
        }

        // limit tickrate to 60/s
        //if(delta.count() > 8){
        ticks++;

        for (int i = 0; i < os.am->num_agents; i++) {
            os.am->eye_input_b[i] = 0;
            os.am->eye_input_g[i] = 0;
            os.am->eye_input_r[i] = 0;
            for (int j = 0; j < os.am->num_agents; j++) {
                if (i != j) {
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
                        os.am->eye_input_b[i] = os.am->colors[j].b;
                        os.am->eye_input_g[i] = os.am->colors[j].g;
                        os.am->eye_input_r[i] = os.am->colors[j].r;
                        //log(i << " working: " << ang_diff);
                    }
                    //if (i == 0) {
                    //    os.am->positions[i] += {0, -0.5};
                    //}
                }
            }
            ArrayXn input(3);
            input << os.am->eye_input_b[i], os.am->eye_input_g[i], os.am->eye_input_r[i];
            ArrayXn res = os.am->MLPs[i].eval(input);
            os.am->angles[i] = fmod(os.am->angles[i] + res[1], 360);

            if (os.am->eye_input_b[i] != 0 || os.am->eye_input_g[i] != 0 || os.am->eye_input_r[i] != 0) {
                log((int)os.am->eye_input_b[i] << " " << (int)os.am->eye_input_g[i] << " " << (int)os.am->eye_input_r[i]);
                log("res: " << res[1] << " " << os.am->positions[i].x << " " << os.am->positions[i].y);
            }
            os.am->positions[i] += {res[0] * evo_math::cos(os.am->angles[i]), res[0] * evo_math::sin(os.am->angles[i])};
            //log(res);
        }

        //const auto &window_img = window_texture.getTexture().copyToImage();
        // calculate actions and add them to position for each agent
        //for(int i = 0; i<os.am->num_agents; i++){
        //    std::unique_ptr<actions> a = std::move(calculate_action(os.am->decision_matrices[i]));
        //    os.am->positions[i]+=sf::Vector2f(a->v_x/4, a->v_y/4);
        //}

        // run passed functions
        //auto f_it = function_list.begin();
        //auto a_it = function_args.begin();
        //for(;f_it!=function_list.end() && a_it != function_args.end(); f_it++, a_it++){
        //    (*f_it)(os.am, *a_it);
        //}

        //p_r_engine->get_pixel(100, 100);
        //p_r_engine->get_pixel(101, 100);
        //p_r_engine->get_pixel(102, 100);
        time_end = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> delta = time_now - time_end;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(8ms - delta);
        //}
    }
}