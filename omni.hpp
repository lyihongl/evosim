#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

#include "agent_manager.hpp"

//class render_engine;
//class actions_engine;
//class agent_manager;
struct omni_sight {
   public:
    //render_engine *re;
    //actions_engine *ae;
    agent_manager *am;
    Eigen::ArrayXi layers;
    std::vector<std::unique_ptr<sf::Color[]>> screen_dat;
    sf::RenderTexture scent_map;

    //void init_screen_dat(int w, int h);
    std::vector<sf::RenderTexture> render_targets;
    unsigned int window_w, window_h;
    //sf::RenderTexture vision_layer;
    unsigned int tps;
    int longest_alive_index;

    omni_sight(int w, int h, std::size_t render_layers) : layers(3),
                                                          render_targets(render_layers) ,
                                                          screen_dat(render_layers)
    {
        for (auto &it : render_targets) {
            it.create(w, h);
        }

        for(auto &it : screen_dat) {
            it = std::unique_ptr<sf::Color[]>(new sf::Color[1600*900*4]);
        }
        window_w = w;
        window_h = h;
        longest_alive_index = -1;
        tps = 0;
        am = nullptr;
        layers << 6, 8, 3;
    }

    const sf::Color &get_color_from_buff(const std::size_t buffer, const unsigned int x, const unsigned int y){
        return screen_dat[buffer][window_w*(window_h-y) + x];
    }
};