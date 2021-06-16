#include "perfect_game_controller.hpp"
#include <tuple>

void PerfectGameController::calulateNextMove() {
    std::tuple<int, int, int> result = this->max();
    int y = std::get<1>(result), x = std::get<2>(result);
    this->match_field[y][x] = Field::CIRCLE;
}

std::tuple<int, int, int> PerfectGameController::max() {
    int best_result = -2, best_x = 0, best_y = 0;
    for(int y=0; y<3; y++) {
        for(int x=0; x<3; x++) {
            if(this->match_field[y][x] == Field::EMPTY) {
                this->match_field[y][x] = Field::CIRCLE;
                std::optional<GameStatus> gameStatus = this->whoWon();
                int result;
                if(gameStatus.has_value()) {
                    if(gameStatus.value() == GameStatus::TIE) {
                        result = 0;
                    }
                    else if(gameStatus.value() == GameStatus::COMPUTER) {
                        result = 1;
                    }
                    else {
                        result = -1;
                    }
                }
                else {
                    result = this->min();
                }
                if(result > best_result) {
                    best_y = y;
                    best_x = x;
                    best_result = result;
                }
                this->match_field[y][x] = Field::EMPTY;
            }
        }
    }
    return std::tuple<int, int, int>(best_result, best_y, best_x);
}

int PerfectGameController::min() {
    int best_result = 2;
    for(int y=0; y<3; y++) {
        for(int x=0; x<3; x++) {
            if(this->match_field[y][x] == Field::EMPTY) {
                this->match_field[y][x] = Field::CROSS;
                std::optional<GameStatus> gameStatus = this->whoWon();
                int result;
                if(gameStatus.has_value()) {
                    if(gameStatus.value() == GameStatus::TIE) {
                        result = 0;
                    }
                    else if(gameStatus.value() == GameStatus::COMPUTER) {
                        result = 1;
                    }
                    else {
                        result = -1;
                    }
                }
                else {
                    result = std::get<0>(this->max());
                }
                if(result < best_result) {
                    best_result = result;
                }
                this->match_field[y][x] = Field::EMPTY;
            }
        }
    }
    return best_result;
}