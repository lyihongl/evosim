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
#include "asset_manager.hpp"

#define AGENT_SIZE 23.f

void draw_angled_line(sf::RenderWindow& w, double theta);

class render_engine{
    public:

        render_engine(int width, int height, std::string title);
        sf::RenderWindow window;
        sf::RenderTexture window_contents_texture;
        sf::Image window_contents_image;

        std::vector< generic_func_render > function_list;
        std::vector<void*> function_args;
        std::vector<sf::CircleShape> agents;
        agent_manager* p_am;
        asset_manager* p_assetm;

        status add_function(generic_func_render f, void* a); 
        void main_loop();
        void draw_angled_line(sf::RenderTarget& target, sf::Vector2f& position, const double length, const int angle);
        sf::Image& get_window_image();
        uint32_t get_pixel(unsigned int x, unsigned int y);
};

render_engine::render_engine(int width, int height, std::string title): 
window{sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar},
window_contents_texture{} {
    window_contents_texture.create(window.getSize().x, window.getSize().y);
    window_contents_image.create(window.getSize().x, window.getSize().y);
    window.setActive(false);
};

void render_engine::main_loop(){
    int counter = 0;

    std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end_fps = std::chrono::system_clock::now();
    
    int frames = 0, fps = 0;
    sf::Text fps_text;
    fps_text.setFont(p_assetm->font_map["times"]);
    fps_text.setFillColor(sf::Color::Red);
    fps_text.setCharacterSize(20);



    for (;window.isOpen();) {
        sf::Event event;
        for (;window.pollEvent(event);) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        time_now = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> delta = time_now - time_end;
        std::chrono::duration<double, std::milli> delta_second = time_now - time_end_fps;

        if(delta_second.count()>1000){
            fps = frames;
            frames = 0;
            time_end_fps = std::chrono::system_clock::now();
        }

        if(delta.count() > 16){
            frames++;
            window.clear();
            window_contents_texture.clear();
            fps_text.setString("FPS: "+std::to_string(fps));
            fps_text.setOrigin(sf::Vector2f{-20, 0});
            window.draw(fps_text);

            sf::CircleShape template_circle(AGENT_SIZE);
            template_circle.setOrigin(AGENT_SIZE, AGENT_SIZE);
            for(int i = 0; i<p_am->num_agents; i++){
                if(p_am->types[i] == agent_type::pred)
                    template_circle.setFillColor(sf::Color::Red);
                else
                    template_circle.setFillColor(sf::Color::Green);
                template_circle.setPosition(p_am->positions[i]);
                window.draw(template_circle);
                window_contents_texture.draw(template_circle);
                draw_angled_line(window, p_am->positions[i], 50, evo_math::normalize_angle(p_am->angles[i]));
                draw_angled_line(window, p_am->positions[i], 50, evo_math::normalize_angle(p_am->angles[i]+90));
                draw_angled_line(window, p_am->positions[i], 50, evo_math::normalize_angle(p_am->angles[i]+180));
                draw_angled_line(window, p_am->positions[i], 50, evo_math::normalize_angle(p_am->angles[i]+270));
            }
            window.display();
            window_contents_texture.display();
            //log((int)window_contents_texture.getTexture().copyToImage().getPixel(100, 100).r);
            time_end = std::chrono::system_clock::now();
        }
    }
}
status render_engine::add_function(generic_func_render f, void* a){
    function_list.push_back(f);
    function_args.push_back(a);
    return status::success;
}

void render_engine::draw_angled_line(sf::RenderTarget& target, sf::Vector2f& position, const double length, const int angle){
    sf::Vector2f end{position.x+evo_math::cos(angle)*length, position.y-evo_math::sin(angle)*length};
    sf::Vertex line[] = {
        position,
        end
    };
    target.draw(line, 2, sf::Lines);
}
sf::Image& render_engine::get_window_image(){
    window_contents_image = window_contents_texture.getTexture().copyToImage();
    return window_contents_image;
}

uint32_t render_engine::get_pixel(unsigned int x, unsigned int y){
    auto color = get_window_image().getPixel(x, y);
    //log((int)color.r);
    return color.toInteger();
}