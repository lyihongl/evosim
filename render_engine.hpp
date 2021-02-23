#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
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
    template <typename T>
    void draw_to_target(std::vector<sf::RenderTexture> &targets, std::size_t target, T t);
    //sf::Image &get_window_image();
    //uint32_t get_pixel(unsigned int x, unsigned int y);
};

template <typename T>
void render_engine::draw_to_target(std::vector<sf::RenderTexture> &targets, std::size_t target, T t) {
    targets[target].draw(t);
}

render_engine::render_engine(int width, int height, std::string title, omni_sight &os) : os{os}, window{sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar} {
    window.setFramerateLimit(80);
    //window.setVerticalSyncEnabled(true);
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

    //char dat[2000*4][2000*4]{0};
    sf::Color *dat = (sf::Color *)malloc(1600 * 900 * sizeof(sf::Color));

    //sf::RenderTexture &ae_texture = os.vision_layer;

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

        //if (delta.count() > 16) {
        ImGui::SFML::Update(window, delta_time_sf.restart());
        //ImGui::SetNextWindowPos(ImVec2{0, 0});
        ImGui::Begin("Debugging");
        ////std::string
        ImGui::Text(std::string("FPS: " + std::to_string(fps)).c_str());
        ImGui::Text(std::string("TPS: " + std::to_string(os.tps)).c_str());
        ImGui::Text(std::string("Longest Alive Index: " + std::to_string(os.longest_alive_index)).c_str());

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

        for (auto &it : os.render_targets) {
            it.clear();
        }
        //ae_texture.clear();
        //window_contents_texture.clear();
        fps_text.setString("FPS: " + std::to_string(fps));
        fps_text.setOrigin(sf::Vector2f{-20, 0});
        window.draw(fps_text);

        sf::CircleShape template_circle(AGENT_SIZE);
        template_circle.setOrigin(AGENT_SIZE, AGENT_SIZE);
        for (int i = 0; i < os.am->num_agents; i++) {
            //for (auto it = os.am->active_agent_set.begin(); it != os.am->active_agent_set.end(); it++) {
            //log("agent size: "<<os.am->num_agents <<" it: "<<*it);
            if (os.am->active_agent_set.find(i) == os.am->active_agent_set.end()) continue;
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(os.am->colors[i].r, os.am->colors[i].g, os.am->colors[i].b)));
            ImGui::Text(std::string("[=] ").c_str());
            ImGui::SameLine();
            ImGui::PopStyleColor();
            ImGui::Text(std::string("Agent: " + std::to_string(i) +
                                    " Energy: " + std::to_string(os.am->energy[i]) +
                                    " Spike: " + std::to_string(os.am->spike[i]) +
                                    " Time Alive: " + std::to_string(os.am->time_alive[i]))
                            .c_str());
            //log("f");
            //if (os.am->types[i] == agent_type::pred)
            //    template_circle.setFillColor(sf::Color::Red);
            //else
            //    template_circle.setFillColor(sf::Color::Green);
            template_circle.setFillColor(os.am->colors[i]);
            template_circle.setPosition(os.am->positions[i]);
            template_circle.setOutlineThickness(1);
            template_circle.setOutlineColor(sf::Color(255, 255, 255));
            os.render_targets[0].draw(template_circle);
            draw_to_target(os.render_targets, 0, template_circle);
            //ae_texture.draw(template_circle);
            draw_angled_line(os.render_targets[0], os.am->positions[i], 50, os.am->angles[i]);
            draw_angled_line(os.render_targets[0], os.am->positions[i], 50, os.am->angles[i] + os.am->fovs[i]);
            draw_angled_line(os.render_targets[0], os.am->positions[i], 50, os.am->angles[i] - os.am->fovs[i]);
        }
        window.draw(sf::Sprite(os.render_targets[0].getTexture()));
        ImGui::End();

        ImGui::SFML::Render(window);
        int counter = 0;
        for (auto &it : os.render_targets ) {
            glBindTexture(GL_TEXTURE_2D, it.getTexture().getNativeHandle());
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, os.screen_dat[counter].get());
            glBindTexture(GL_TEXTURE_2D, 0);
            //counter++;
        }
        //for(int i = 0; i<os.render_targets.size(); i++){
        //    glBindTexture(GL_TEXTURE_2D, os.render_targets[i].getTexture().getNativeHandle());
        //    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, os.screen_dat[i].get());
        //    glBindTexture(GL_TEXTURE_2D, 0);
        //}

        //glBindTexture(GL_TEXTURE_2D, os.render_targets[0].getTexture().getNativeHandle());
        //glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, os.screen_dat.get());
        ////log((int)os.screen_dat[800*1600+100].r);
        ////log((int)(*((sf::Color *)(dat + (1600-100) * 900 * 4))).r);

        //glBindTexture(GL_TEXTURE_2D, 0);

        window.display();
        //ae_texture.display();
        //for(int i = 0; i<900; i++){
        //    for(int j = 0; j<1600; j++){
        //        log(j<<" "<<i<<" "<<(int)os.screen_dat[i*1600+j].r<<" "<<(int)os.screen_dat[i*1600+j].g<<" "<<(int)os.screen_dat[i*1600+j].b);
        //    }
        //}
        //break;

        //window_contents_texture.display();
        //window_contents_image = window_contents_texture.getTexture().copyToImage();
        //log((int)window_contents_texture.getTexture().copyToImage().getPixel(100, 100).r);
        time_end = std::chrono::system_clock::now();
        //}
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