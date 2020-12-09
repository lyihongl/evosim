#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <Eigen/Dense>
#include "agent_manager.hpp"
#include "render_engine.hpp"
#include "brain.hpp"

int main() {
    Eigen::MatrixXd test(2, 3);
    Eigen::MatrixXd test2(3, 3);
    test << 1, 2, 3,
            4, 5, 6;
    test2 <<    1, 1, 1,
                1, 1, 1,
                1, 1, 1;
    std::cout<<test*test2<<std::endl;
    agent_manager am{};
    am.add_agent(sf::Vector2f{0, 0}, agent_type::pred);
    am.add_decision_matrix(0, test);
    am.add_decision_matrix(0, test2);
    std::cout<<test(0, 1)<<std::endl;
    //render_engine r{1600, 900, "testing"};
    //r.circle_positions.push_back(sf::Vector2f{0.f, 100.f});
    //r.circle_positions.push_back(sf::Vector2f{100.f, 100.f});
    //r.circle_positions.push_back(sf::Vector2f{200.f, 100.f});
    //r.circle_positions.push_back(sf::Vector2f{900.f, 900.f});
    //std::thread render_thread{&render_engine::main_loop, &r};
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
