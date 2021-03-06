#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
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
  // render_engine* p_r_engine;
  std::vector<generic_func> function_list;
  std::vector<void *> function_args;
  omni_sight &os;
  // agent_manager* os.am;
  sf::RenderTexture window_texture;
  sf::Image window_image;
  status add_function(generic_func_render f, void *a);
  bool run{false};
  void run_engine();
  actions_engine(int width, int height, omni_sight &os);
  // int tps;
  std::size_t longest_alive_index;
};
actions_engine::actions_engine(int width, int height, omni_sight &os) : os{os} {
  window_texture.create(width, height);
}

void actions_engine::run_engine() {
  std::chrono::time_point<std::chrono::system_clock> time_now =
      std::chrono::system_clock::now();
  std::chrono::time_point<std::chrono::system_clock> time_end =
      std::chrono::system_clock::now();
  std::chrono::time_point<std::chrono::system_clock> time_end_tps =
      std::chrono::system_clock::now();
  int ticks = 0;
  // tps = 0;
  int i = 0;
  bool sec_passed = false;
  unsigned int mutate_max = 0;
  std::size_t mutate_max_index = 0;
  // char *dat = (char *)malloc(1600 * 900 * 4);
  // float omega = 0.15;
  std::vector<sf::Vector2f> start_scan(8);
  std::vector<int> scan_angle(8);
  std::vector<std::vector<sf::Vector2f>> scan_points(
      8, std::vector<sf::Vector2f>(30));
  for (; run;) {
    time_now = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> delta_second =
        time_now - time_end_tps;

    if (delta_second.count() > 1000) {
      os.tps = ticks;
      ticks = 0;
      time_end_tps = std::chrono::system_clock::now();
      sec_passed = true;
    }

    // limit tickrate to 60/s
    // if(delta.count() > 8){
    ticks++;
    // sf::Texture::bind(&window_texture.getTexture());
    // glBindTexture(GL_TEXTURE_2D,
    // window_texture.getTexture().getNativeHandle()); window_image =
    // window_texture.getTexture().copyToImage();
    // window_texture.getTexture().copyToImage();
    // log(window_texture.getTexture().getNativeHandle());

    for (int i = 0; i < os.am->num_agents; i++) {
      evo_math::start_scan_positions(start_scan, scan_angle, os.am->angles[i]);
      for (int j = 0; j < start_scan.size(); j++) {
        start_scan[j] +=
            {os.am->positions[i].x, os.window_h - os.am->positions[i].y};
        evo_math::populate_line_points(scan_points[j], 30, start_scan[j], 300,
                                       (int)scan_angle[j]);
      }
      // for(int k = 0; k<scan_points.size(); k++){
      //    for(int j = 0; j<scan_points[k].size(); j++){
      //        log_precision("points: "<<k<<" "<<j<<" "<<scan_points[k][j].x<<"
      //        "<<scan_points[k][j].y, 6);
      //    }
      //}
      // for(auto &it: scan_points){
      //    for(auto &jt: it){
      //        log("points: "<<jt.x <<" "<<jt.y);
      //    }
      //}
      // break;
      // for(auto &it : start_scan){
      //    (it)+={os.am->positions[i].x, os.window_h - os.am->positions[i].y};
      //    //it.y = os.window_h - it.y;
      //    //log(it.x << " "<<it.y);
      //}
      // for(auto &it: scan_angle){
      //    log("angle: "<<it);
      //}
      // break;
      // evo_math::populate_line_points()
      // glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, dat);
      // log(*((int*)(dat + 100*900*4+100*4)));
      // if (os.am->active_agent_set.find(i) == os.am->active_agent_set.end())
      // continue; os.am->eye_input_b[i] = 0; os.am->eye_input_g[i] = 0;
      // os.am->eye_input_r[i] = 0;
      // if (sec_passed) {
      //    os.am->time_alive[i] += 1;
      //}
      // int seen = 0;
      // for (int j = 0; j < os.am->num_agents && seen < 4; j++) {
      //    if (i != j) {
      //        float dist = evo_math::abs_dist(os.am->positions[i] -
      //        os.am->positions[j]); if ((dist < AGENT_SIZE && (os.am->spike[i]
      //        || os.am->spike[j]))) {
      //            os.am->remove_agent(j);
      //            os.am->energy[i] = (os.am->energy[i] + 20 <= 100) ?
      //            os.am->energy[i] + 20 : 100;
      //        }

      //        sf::Vector2f pos = os.am->positions[j] - os.am->positions[i];
      //        //log( "i: " <<i <<" "<< pos.x << " " << pos.y );
      //        float langle = os.am->angles[i] + os.am->fovs[i];
      //        float rangle = os.am->angles[i] - os.am->fovs[i];

      //        //log(pos.x <<" "<<-pos.y <<" "<<std::atan2(-pos.y,
      //        pos.x)*180/M_PI); float atan = std::atan2(-pos.y, pos.x) * 180 /
      //        M_PI;
      //        //if(atan < 0) atan += 360;
      //        float ang_diff = os.am->angles[i] - atan;
      //        if (std::abs(ang_diff) > 180) ang_diff = 360 -
      //        std::abs(ang_diff); ang_diff = std::abs(ang_diff);

      //        if (ang_diff < os.am->fovs[i]) {
      //            seen++;
      //            os.am->eye_input_b[i] += os.am->colors[j].b / dist;
      //            os.am->eye_input_g[i] += os.am->colors[j].g / dist;
      //            os.am->eye_input_r[i] += os.am->colors[j].r / dist;
      //            //log(i << " working: " << ang_diff);
      //        }
      //        //if (i == 0) {
      //        //    os.am->positions[i] += {0, -0.5};
      //        //}
      //    }
      //}
      // ArrayXn input(6);
      // input << os.am->eye_input_b[i], os.am->eye_input_g[i],
      // os.am->eye_input_r[i], os.am->angular_v[i], os.am->velocity[i],
      // (int)os.am->spike[i];
      ////log("input: " << input);
      // ArrayXn res = os.am->MLPs[i].eval(input);
      // os.am->angles[i] = fmod(os.am->angles[i] + (res[1]-0.5) * 15, 360);
      // os.am->angular_v[i] = (res[1]-0.5)*15;
      // os.am->velocity[i] = (res[0]-0.5);

      // auto it = std::max_element(os.am->time_alive.begin(),
      // os.am->time_alive.end()); longest_alive_index =
      // std::distance(os.am->time_alive.begin(), it);

      ////if(os.am->time_alive[i]>mutate_max){
      ////    mutate_max = os.am -> time_alive[i];
      ////    mutate_max_index = i;
      ////}

      ////if (os.am->eye_input_b[i] != 0 || os.am->eye_input_g[i] != 0 ||
      /// os.am->eye_input_r[i] != 0) { /    log((int)os.am->eye_input_b[i] << "
      ///" << (int)os.am->eye_input_g[i] << " " << (int)os.am->eye_input_r[i]);
      ////    log("res: " << res[1] << " " << os.am->positions[i].x << " " <<
      /// os.am->positions[i].y);
      ////}
      // os.am->energy[i] -= 0.05;
      // if (os.am->energy[i] <= 0) {
      //    os.am->remove_agent(i);
      //}
      // if (os.am->empty_slots_stack.size() > 0) {
      //    os.am->add_agent(sf::Vector2f{(std::rand() % 800) + 100,
      //    (std::rand() % 800) + 100}, sf::Color(std::rand() % 255, std::rand()
      //    % 255, std::rand() % 255), MLP(os.layers, 1), std::rand() % 360);
      //}
      // os.am->positions[i] += {(res[0]-0.5) * evo_math::cos(os.am->angles[i]),
      // (res[0]-0.5) * evo_math::sin(os.am->angles[i])};

      // os.am->spike[i] = (res[2] >= 0.5) ? 1 : 0;
    }
    // break;
    // longest_alive_index = mutate_max_index;
    sec_passed = (sec_passed) ? false : sec_passed;
    // if(sec_passed) {
    //    sec_passed = false;
    //}
    time_end = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> delta = time_end - time_now;
    using namespace std::chrono_literals;
    //log(delta.count());
    std::this_thread::sleep_for(8ms - delta);
    //}
  }
}