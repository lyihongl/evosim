#pragma once
#include <unordered_map>
#include "agent_manager.hpp"
#define generic_func_render std::function<void*(sf::Window&, agent_manager*, void*)>
#define generic_func std::function<void*(agent_manager*, void*)>
#define AGENT_SIZE 10.f

//struct screen_dat_buffer{
//    std::unique_ptr<sf::Color[]> screen_dat
//    screen_dat_buffer();
//};

//class generic_args{
//    template <typename T>
//    std::unordered_map<std::string, T> m;
//};