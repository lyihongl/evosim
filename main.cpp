#include <SFML/System.hpp> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Eigen/Dense>
#include <thread>
#include <memory>
#include "omni.hpp"
#include "agent_manager.hpp"
#include "render_engine.hpp"
#include "brain.hpp"
#include "actions_engine.hpp"
#include "math.hpp"
#include "asset_manager.hpp"
#include "threading_engine.hpp"
#include "MLP.hpp"

int main() {
    //return 0;
    srand((unsigned int) time(0));
    //std:: cout << (-400 % 360) << std::endl;
    evo_math::init_trig_table();
    Eigen::MatrixXd test(1, 3);
    Eigen::MatrixXd test2(3, 3);
    test << 0.5, 0.8, 0.1;
    test2 << 1, 4, 1,
        1, 5, 1,
        1, 1, 1;
    //std::cout<<test*test2<<std::endl;
    std::unique_ptr<agent_manager> am = std::unique_ptr<agent_manager>(new agent_manager{});
    asset_manager assetm;
    assetm.load_assets();



    //MLP m(layers, 1);
    //ArrayXn input(3);
    //input << 1, 2, 3;
    //input.conservativeResize(layers[0]+1);
    //evo_math::print_vector("WEIGHTS", m.weights);
    //std::cout << m.eval(input) << std::endl;
    //std::cout << m.eval(input) << std::endl;
    //evo_math::print_vector("OUTPUT", m.eval(input));
    //ArrayXn input;
    //m.eval();

    //am -> add_agent(sf::Vector2f{300, 300}, sf::Color(0, 255, 0), MLP(layers, 1), 45);
    //am -> add_decision_matrix(0, test);
    //am -> add_decision_matrix(0, test2);

    //am -> add_decision_matrix(1, test);
    //am -> add_decision_matrix(1, test2);
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
    log("angle test: "<< evo_math::angle_between(210, 170, 180));
    log("angle test: "<< evo_math::angle_between(45, -270, 46));
    for (const auto &a : test3)
    {
        log( a.x << " " << a.y );
    }

    //std::thread render_thread{&begin_render_thread};
    //render_thread.join();
    omni_sight os{};
    //MLP breed1(os.layers, 1);
    //MLP breed2(os.layers, 1);
    //std::vector<Eigen::MatrixXd> breed3 = cross_breed(breed1.weights, breed2.weights);
    //log("breed1");
    //for(auto &it : breed1.weights){
    //    std::cout << it << std::endl << std::endl;
    //}
    //log("breed2");
    //for(auto &it : breed2.weights){
    //    std::cout << it << std::endl << std::endl;
    //    std::cout << it.rows() << std::endl << std::endl;
    //    std::cout << it.cols() << std::endl << std::endl;
    //    //it.conservativeResize(os.layers[0]+1);
    //    //std::cout << it.rows() << std::endl << std::endl;
    //    //std::cout << it.cols() << std::endl << std::endl;
    //}
    //log("breed3");
    //for(auto &it : breed3){
    //    std::cout << it << std::endl << std::endl;
    //}
    //std::vector<Eigen::MatrixXd> breed4 = vary_weights(breed3, os.layers);
    //log("breed4");
    //for(auto &it : breed4){
    //    std::cout << it << std::endl << std::endl;
    //}
    //return 0;
    for(int i = 0; i<1000; i+=100){
        for(int j = 0; j<1000; j+=100){
            am -> add_agent(sf::Vector2f{i, j}, sf::Color(std::rand()%255+1, std::rand()%255+1, std::rand()%255), MLP(os.layers, 1), std::rand()%360);
        }
    }
    //for(auto it = am->active_agent_set.begin(); it != am->active_agent_set.end(); it++){
    //    log("it: " <<*it);
    //}
    log("set size: "<<am->active_agent_set.size());
    render_engine r{1600, 900, "testing", os};
    r.p_assetm = &assetm;
    actions_engine a{os};
    os.ae = &a;
    os.re = &r;
    os.am = am.get();
    //a.p_am = am.get();
    //a.p_r_engine = &r;
    //r.ae = &a;
    //r.p_am = am.get();

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
