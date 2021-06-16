#pragma once
#include "perfect_game_controller.hpp"
#include "random_game_controller.hpp"

class NormalGameController : public PerfectGameController, public RandomGameController {
public:  
    virtual void calulateNextMove();
};