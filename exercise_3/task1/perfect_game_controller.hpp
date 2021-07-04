#pragma once
#include "game_controller.hpp"

class PerfectGameController : virtual public GameController {
public:
    virtual void calulateNextMove();

private:
    std::tuple<int, int, int> max();
    int min();
};