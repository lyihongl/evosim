#include <SFML/Graphics.hpp>
#include <iostream>
#include "agent_manager.hpp"
#include "render_engine.hpp"

int main() {
    render_engine r{200, 200, "testing"};
    r.main_loop();
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
