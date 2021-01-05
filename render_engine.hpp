#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>
#include <functional>
#include "error_handling.hpp"
#include "types.hpp"
#include "logging.hpp"
#include "math.hpp"

#define AGENT_SIZE 23.f

void draw_angled_line(sf::RenderWindow& w, double theta);

class render_engine{
    public:

        render_engine(int width, int height, std::string title);
        sf::RenderWindow window;
        sf::Texture window_contents_texture;
        sf::Image window_contents_image;

        //void render_agents(std::vector<position> &positions);

        std::vector< generic_func_render > function_list;
        std::vector<void*> function_args;
        std::vector<sf::CircleShape> agents;
        agent_manager* am;
        //std::vector<sf::Vector2f> circle_positions;

        status add_function(generic_func_render f, void* a); 
        void main_loop();
        void draw_angled_line(const sf::Vector2f& position, const double length, const int angle);
};

render_engine::render_engine(int width, int height, std::string title): 
window{sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close},
window_contents_texture{} {
    window_contents_texture.create(window.getSize().x, window.getSize().y);
    window_contents_image.create(window.getSize().x, window.getSize().y);
    //std::cout<<"texture size: "<<window_contents_texture.getSize().x<<std::endl;
    window.setActive(false);
};

//void render_engine::render_agents(std::vector<position> &positions){
//    //render circles based on position
//    for(auto& pos: positions){
//        
//    }
//}

void render_engine::main_loop(){
    int counter = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::CircleShape template_circle(AGENT_SIZE);
        template_circle.setOrigin(AGENT_SIZE, AGENT_SIZE);
        //for(auto const& it: circle_positions){
            //template_circle.setPosition(it);
            //window.draw(template_circle);
        //}
        //log_err("here");
        for(int i = 0; i<am->num_agents; i++){
            if(am->types[i] == agent_type::pred)
                template_circle.setFillColor(sf::Color::Red);
            else
                template_circle.setFillColor(sf::Color::Green);
            template_circle.setPosition(am->positions[i]);
            log("Postion"<<" "<<(am->positions[i].x)<<" "<<(am->positions[i].y));
            //std::cout<<"position"
            window.draw(template_circle);
            draw_angled_line(am->positions[i], 50, 90);
        }
        //log_err("here");

        /*
        auto f_it = function_list.begin();
        auto a_it = function_args.begin();

        for(;f_it!=function_list.end() && a_it != function_args.end(); f_it++, a_it++){
            (*f_it)(window, am, *a_it);
        }
        */

        //can multithread here
        window_contents_texture.update(window);
        //std::cout<<"pixels: " <<window_contents_texture.copyToImage().getPixel(100, 100).toInteger()<<std::endl;

        window.display();

    }
}
status render_engine::add_function(generic_func_render f, void* a){
    function_list.push_back(f);
    function_args.push_back(a);
    return status::success;
}

void render_engine::draw_angled_line(const sf::Vector2f& position, const double length, const int angle){
    sf::Vector2f end{position.x+evo_math::cos(angle)*length, position.y-evo_math::sin(angle)*length};
    sf::Vertex line[] = {
        position,
        end
    };
    window.draw(line, 2, sf::Lines);
}