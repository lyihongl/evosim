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
        //vision_layer.create(w, h);
        //screen_dat = std::unique_ptr<sf::Color>(new sf::Color[w * h * 4]);
        //screen_dat = std::shared_ptr<char>(new char[w*h*4]);
        longest_alive_index = -1;
        //re = nullptr;
        //ae = nullptr;
        tps = 0;
        am = nullptr;
        layers << 6, 8, 3;
    }

    //~omni_sight(){
    //    delete screen_dat;
    //}

    //omni_sight(render_engine *re, actions_engine *ae, agent_manager *am):layers(3){
    //    //this -> re = re;
    //    //this -> ae = ae;
    //    //this -> am = am;
    //    this->layers << 3,6,3;
    //}
};