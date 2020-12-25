#pragma once
#include "agent_manager.hpp"
#define generic_func_render std::function<void*(sf::Window&, agent_manager*, void*)>
#define generic_func std::function<void*(agent_manager*, void*)>