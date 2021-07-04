#pragma once
#include "game_controller.hpp"

class RandomGameController : virtual public GameController {
public:   
    virtual void calulateNextMove();
};