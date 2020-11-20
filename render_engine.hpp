#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "math2d.hpp"
#include "error_handling.hpp"
#include "types.hpp"

class render_engine{
    public:

        render_engine(int width, int height, std::string title);
        sf::RenderWindow window;

        void render_agents(std::vector<position> &positions);

        std::vector< generic_func > function_list;
        std::vector<void*> function_args;

        status add_function(generic_func f, void* a);

        void main_loop();
};

render_engine::render_engine(int width, int height, std::string title): window{sf::VideoMode(width, height), title} {};

void render_engine::render_agents(std::vector<position> &positions){
    //render circles based on position
    for(auto& pos: positions){

    }
}

void render_engine::main_loop(){
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        auto f_it = function_list.begin();
        auto a_it = function_args.begin();

        for(;f_it!=function_list.end() && a_it != function_args.end(); f_it++, a_it++){
            (*f_it)(*a_it);
        }
        window.display();
    }
}
status render_engine::add_function(generic_func f, void* a){
    function_list.push_back(f);
    function_args.push_back(a);
    return status::success;
}
