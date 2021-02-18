#pragma once


class render_engine;
class actions_engine;
class agent_manager;
struct omni_sight{
    public:
    render_engine *re;
    actions_engine *ae;
    agent_manager *am;
    Eigen::ArrayXi layers;
    omni_sight():layers(3){
        re = nullptr;
        ae = nullptr;
        am = nullptr;
        layers << 6,8,3;
    }

    omni_sight(render_engine *re, actions_engine *ae, agent_manager *am):layers(3){
        this -> re = re;
        this -> ae = ae;
        this -> am = am;
        this->layers << 3,6,3;
    }
};