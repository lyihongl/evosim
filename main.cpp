#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <thread>

#include "MLP.hpp"
#include "actions_engine.hpp"
#include "agent_manager.hpp"
#include "asset_manager.hpp"
#include "brain.hpp"
#include "math.hpp"
#include "omni.hpp"
#include "render_engine.hpp"
#include "threading_engine.hpp"

int main() {
    srand((unsigned int)time(0));
    evo_math::init_trig_table();

    // TESTING

    //std::vector<sf::Vector2f> test(30);
    //sf::Vector2f testpoint{100, 800};
    //log("trig test "<<evo_math::sin(135) << " "<<evo_math::cos(135));
    //evo_math::populate_line_points(test, 30, testpoint, 300, 135);
    //for(auto &it: test){
    //    log_precision(it.x <<" "<<it.y, 6)
    //}

    //std::vector<sf::Vector2f> start_scan(8);
    //std::vector<int> scan_angle(8);
    //std::vector<std::vector<sf::Vector2f>> scan_points(8, std::vector<sf::Vector2f>(30));
    //evo_math::start_scan_positions(start_scan, scan_angle, 12);
    //for (int j = 0; j < start_scan.size(); j++) {
    //    start_scan[j] += {100, 800};
    //    evo_math::populate_line_points(scan_points[j], 30, start_scan[j], 300, scan_angle[j]);
    //    log("start scan: " << scan_angle[j] << " " << start_scan[j].x << " " << start_scan[j].y);
    //}
    //for (int k = 0; k < scan_points.size(); k++) {
    //    for (int j = 0; j < scan_points[k].size(); j++) {
    //        log_precision("points: " << k << " " << j << " " << scan_points[k][j].x << " " << scan_points[k][j].y, 6);
    //    }
    //}

    //

    std::unique_ptr<agent_manager> am = std::unique_ptr<agent_manager>(new agent_manager{});
    asset_manager assetm;
    assetm.load_assets();
    log("angle test: " << evo_math::angle_between(210, 170, 180));
    log("angle test: " << evo_math::angle_between(45, -270, 46));

    // layers

    omni_sight os{1600, 900, 6};
    am->add_agent(sf::Vector2f{100, 100}, sf::Color(123, 255, 22), MLP(os.layers, 1), std::rand() % 360);
    for (auto it = am->active_agent_set.begin(); it != am->active_agent_set.end(); it++) {
        log("it: " << *it);
    }
    log("set size: " << am->active_agent_set.size());
    render_engine r{1600, 900, "testing", os};
    r.p_assetm = &assetm;
    actions_engine a{1600, 900, os};
    os.am = am.get();
    a.run = true;

    std::thread calc_thread{&actions_engine::run_engine, &a};

    r.main_loop();
    a.run = false;

    calc_thread.join();

    return 0;
}
