#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "math2d.hpp"

class render_engine{
    public:

        render_engine(int width, int height, std::string title);
        sf::RenderWindow window;

        void render_agents(std::vector<position> &positions);

        std::vector<void*(*)()> function_list;

        void main_loop();
};

render_engine::render_engine(int width, int height, std::string title): window{sf::VideoMode(width, height), title} {};

void render_engine::render_agents(std::vector<position> &positions){
    //render circles based on position
}

void render_engine::main_loop(){
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        //window.draw(shape);
        window.display();
    }
}
