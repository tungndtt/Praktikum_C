#include "random_game_controller.hpp"
#include "perfect_game_controller.hpp"
#include "normal_game_controller.hpp"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>

int main() {
    std::vector<GameController*> gameModes = {
        new RandomGameController(),
        new PerfectGameController(),
        new NormalGameController(),
    };

    srand(time(NULL));

    
    while(true) {
        std::cout << "============================= MODE OPTIONS =============================" << std::endl;
        int mode;
        while(true) {
            std::cout << "Choose BOT mode: RANDOM (0) | PERFECT (1) | NORMAL (2) | EXIT (3) ..." << std::endl;
            std::cin >> mode;
            if(mode >= 0 && mode <= 2) {
                break;
            } 
            else if(mode == 3) {
                break;
            }
            else {
                std::cout << "!!!! You provided invalid mode !!!!" << std::endl;
            }
        }
        gameModes[mode]->play();
    }

    for(GameController* gameMode : gameModes) {
        delete gameMode;
    }
    
}
