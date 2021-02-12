#pragma once


class render_engine;
class actions_engine;
class agent_manager;
struct omni_sight{
    public:
    render_engine *re;
    actions_engine *ae;
    agent_manager *am;
    omni_sight(){
        re = nullptr;
        ae = nullptr;
        am = nullptr;
    }

    omni_sight(render_engine *re, actions_engine *ae, agent_manager *am){
        this -> re = re;
        this -> ae = ae;
        this -> am = am;
    }
};