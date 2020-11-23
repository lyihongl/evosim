#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "agent_manager.hpp"
#include "render_engine.hpp"

int main() {
    render_engine r{1000, 1000, "testing"};
    r.circle_positions.push_back(sf::Vector2f{0.f, 100.f});
    r.circle_positions.push_back(sf::Vector2f{100.f, 100.f});
    r.circle_positions.push_back(sf::Vector2f{200.f, 100.f});
    r.circle_positions.push_back(sf::Vector2f{900.f, 900.f});
    std::thread render_thread{&render_engine::main_loop, &r};
    render_thread.join();
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
