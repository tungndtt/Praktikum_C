#pragma once

#include <vector> 
#include <optional>

enum Field {
    CROSS, CIRCLE, EMPTY
};

enum GameStatus {
    USER, COMPUTER, TIE
};

class GameController {
public:
    GameController();

    void printMatchfield();
    void getUserInput();
    std::optional<GameStatus> whoWon() const;
    void play();

    virtual void calulateNextMove() = 0;

protected:
    std::vector<std::vector<Field>> match_field;
}; 