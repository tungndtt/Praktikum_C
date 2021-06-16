#include <stdlib.h>
#include <iostream>
#include "random_game_controller.hpp" 

void RandomGameController::calulateNextMove() {
    std::vector<std::vector<int>> emptySlots;
    for(int y=0; y<3; y++) {
        for(int x=0; x<3; x++) {
            if(this->match_field[y][x] == Field::EMPTY) {
                emptySlots.push_back({y, x});
            }
        }
    }
    int idx = rand() % emptySlots.size();
    int y = emptySlots[idx][0], x = emptySlots[idx][1];
    this->match_field[y][x] = Field::CIRCLE;
}