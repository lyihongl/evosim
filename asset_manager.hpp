#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <string>
struct asset_manager{
    std::unordered_map<std::string, sf::Font> font_map;
    void load_assets();
};

void asset_manager::load_assets(){
    font_map["times"].loadFromFile("./assets/fonts/times.ttf");
}