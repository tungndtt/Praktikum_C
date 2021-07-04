#include <cstdlib>
#include "normal_game_controller.hpp"

void NormalGameController::calulateNextMove() {
    bool isRandom = rand()%2==0;

    if(isRandom) {
        this->RandomGameController::calulateNextMove();
    }
    else {
        this->PerfectGameController::calulateNextMove();
    }
}