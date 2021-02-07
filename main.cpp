#define WINDOWS
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Eigen/Dense>
#include <thread>
#include "agent_manager.hpp"
#include "render_engine.hpp"
#include "brain.hpp"
#include "actions_engine.hpp"
#include "math.hpp"
#include "asset_manager.hpp"

int main()
{
    evo_math::init_trig_table();
    Eigen::MatrixXd test(1, 3);
    Eigen::MatrixXd test2(3, 3);
    test << 0.5, 0.8, 0.1;
    test2 << 1, 4, 1,
        1, 5, 1,
        1, 1, 1;
    //std::cout<<test*test2<<std::endl;
    agent_manager am{};
    asset_manager assetm;
    assetm.load_assets();

    am.add_agent(sf::Vector2f{100, 100}, agent_type::pred);
    am.add_agent(sf::Vector2f{50, 100}, agent_type::prey);
    am.add_decision_matrix(0, test);
    am.add_decision_matrix(0, test2);

    am.add_decision_matrix(1, test);
    am.add_decision_matrix(1, test2);
    //for(int i = 0; i<evo_math::RESOLUTION; i++){
    //    std::cout<<evo_math::sin(i)<<" "<<evo_math::cos(i)<<std::endl;
    //}
    //std::unique_ptr<actions> a = std::move( calculate_action(am.decision_matrices[0]));
    //auto m = am.decision_matrices[0][0];
    //auto m = am.get_val<std::vector<Eigen::MatrixXd>>(0)[0];
    //std::cout<<m <<std::endl;
    //std::cout<<am.get_val<Eigen::MatrixXd>()<<std::endl;
    std::vector<sf::Vector2f> test3;
    sf::Vector2f start{0, 0};
    evo_math::populate_line_points(test3, 20, start, 50, 45);
    for (const auto &a : test3)
    {
        log( a.x << " " << a.y );
    }

    //std::thread render_thread{&begin_render_thread};
    //render_thread.join();
    render_engine r{1600, 900, "testing"};
    r.p_assetm = &assetm;
    actions_engine a{};
    a.p_am = &am;
    a.p_r_engine = &r;
    r.p_am = &am;

    //std::thread render_thread{&render_engine::main_loop, &r};
    a.run = true;

    std::thread calc_thread{&actions_engine::run_engine, &a};

    r.main_loop();
    a.run = false;

    calc_thread.join();
    //render_thread.join();

    //pthread_create(&render_thread, NULL, &r.main_loop, NULL);
    //r.main_loop();
    //sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    //agent_manager a{};
    //position p{1, 2};
    //decision_matrix m{};
    //agent_type t = prey;
    //a.add_agent(p, t, m);
    //std::cout<<a.positions[0].x<<" "<<a.positions[0].y<<" "<<a.types[0]<<std::endl;

    return 0;
}
