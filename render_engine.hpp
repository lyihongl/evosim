#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "./imgui-sfml-master/imgui-SFML.h"
#include "./imgui/imgui.h"
#include "actions_engine.hpp"
#include "asset_manager.hpp"
#include "error_handling.hpp"
#include "logging.hpp"
#include "math.hpp"
#include "omni.hpp"
#include "types.hpp"

#define AGENT_SIZE 23.f

void draw_angled_line(sf::RenderWindow &w, double theta);

class render_engine {
   public:
    sf::RenderWindow window;

    //actions_engine *ae;

    //sf::RenderTexture window_contents_texture;
    //sf::Image window_contents_image;

    std::vector<generic_func_render> function_list;
    std::vector<void *> function_args;
    std::vector<sf::CircleShape> agents;
    //const agent_manager *os.am;
    omni_sight &os;
    asset_manager *p_assetm;

    status add_function(generic_func_render f, void *a);
    void main_loop();
    void draw_angled_line(sf::RenderTarget &target, const sf::Vector2f &position, const double length, const int angle);
    std::unordered_map<std::string, std::string> debug_info;
    render_engine(int width, int height, std::string title, omni_sight &os);
    //sf::Image &get_window_image();
    //uint32_t get_pixel(unsigned int x, unsigned int y);
};

render_engine::render_engine(int width, int height, std::string title, omni_sight &os) : os{os}, window{sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar} {
    window.setVerticalSyncEnabled(true);
    //window_contents_texture.create(window.getSize().x, window.getSize().y);
    //window_contents_image.create(window.getSize().x, window.getSize().y);
    window.setActive(false);
};

void render_engine::main_loop() {
    int counter = 0;

    std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> time_end_fps = std::chrono::system_clock::now();

    int frames = 0, fps = 0;
    sf::Text fps_text;
    fps_text.setFont(p_assetm->font_map["times"]);
    fps_text.setFillColor(sf::Color::Red);
    fps_text.setCharacterSize(20);

    ImGui::SFML::Init(window);

    sf::Clock delta_time_sf;

    sf::Color bgColor;

    float color[3] = {0.f, 0.f, 0.f};

    sf::RenderTexture &ae_texture = os.ae->window_texture;

    for (; window.isOpen();) {
        sf::Event event;
        for (; window.pollEvent(event);) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        time_now = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> delta = time_now - time_end;
        std::chrono::duration<double, std::milli> delta_second = time_now - time_end_fps;

        if (delta_second.count() > 1000) {
            fps = frames;
            frames = 0;
            time_end_fps = std::chrono::system_clock::now();
        }

        if (delta.count() > 16) {
            ImGui::SFML::Update(window, delta_time_sf.restart());
            //ImGui::SetNextWindowPos(ImVec2{0, 0});
            ImGui::Begin("Debugging");
            ////std::string
            ImGui::Text(std::string("FPS: " + std::to_string(fps)).c_str());
            ImGui::Text(std::string("TPS: " + std::to_string(os.ae->tps)).c_str());

            ImGui::End();
            //ImGui::Begin("Color Window");
            ////ImGui::Begin("testing");
            //if (ImGui::ColorEdit3("Background color", color)) {
            //    // this code gets called if color value changes, so
            //    // the background color is upgraded automatically!
            //    bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            //    bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            //    bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
            //}
            //ImGui::End();  // end window

            frames++;
            //window.clear();
            window.clear(bgColor);  // fill background with color
            ae_texture.clear();
            //window_contents_texture.clear();
            fps_text.setString("FPS: " + std::to_string(fps));
            fps_text.setOrigin(sf::Vector2f{-20, 0});
            window.draw(fps_text);

            sf::CircleShape template_circle(AGENT_SIZE);
            template_circle.setOrigin(AGENT_SIZE, AGENT_SIZE);
            for (int i = 0; i < os.am->num_agents; i++) {
                //if (os.am->types[i] == agent_type::pred)
                //    template_circle.setFillColor(sf::Color::Red);
                //else
                //    template_circle.setFillColor(sf::Color::Green);
                template_circle.setFillColor(os.am->colors[i]);
                template_circle.setPosition(os.am->positions[i]);
                window.draw(template_circle);
                ae_texture.draw(template_circle);
                draw_angled_line(window, os.am->positions[i], 50, os.am->angles[i]);
                draw_angled_line(window, os.am->positions[i], 50, os.am->angles[i] + os.am->fovs[i]);
                draw_angled_line(window, os.am->positions[i], 50, os.am->angles[i] - os.am->fovs[i]);
            }

            ImGui::SFML::Render(window);
            window.display();
            ae_texture.display();
            //window_contents_texture.display();
            //window_contents_image = window_contents_texture.getTexture().copyToImage();
            //log((int)window_contents_texture.getTexture().copyToImage().getPixel(100, 100).r);
            time_end = std::chrono::system_clock::now();
        }
    }
}
status render_engine::add_function(generic_func_render f, void *a) {
    function_list.push_back(f);
    function_args.push_back(a);
    return status::success;
}

void render_engine::draw_angled_line(sf::RenderTarget &target, const sf::Vector2f &position, const double length, const int angle) {
    //angle = evo_math::normalize_angle(angle);
    //sf::Vector2f end{position.x + evo_math::cos(evo_math::normalize_angle(angle)) * length, position.y - evo_math::sin(evo_math::normalize_angle(angle)) * length};
    sf::Vector2f end{position.x + evo_math::cos(angle) * length, position.y - evo_math::sin(angle) * length};
    sf::Vertex line[] = {
        position,
        end};
    target.draw(line, 2, sf::Lines);
}

//sf::Image &render_engine::get_window_image() {
//    window_contents_image = window_contents_texture.getTexture().copyToImage();
//    return window_contents_image;
//}

//uint32_t render_engine::get_pixel(unsigned int x, unsigned int y) {
//    auto color = get_window_image().getPixel(x, y);
//    return color.toInteger();
//}