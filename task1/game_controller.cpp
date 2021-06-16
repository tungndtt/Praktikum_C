#include <string>
#include <iostream>
#include <cstdlib>
#include "game_controller.hpp"


GameController::GameController() {
    this->match_field = { 
        {Field::EMPTY, Field::EMPTY, Field::EMPTY} , 
        {Field::EMPTY, Field::EMPTY, Field::EMPTY} , 
        {Field::EMPTY, Field::EMPTY, Field::EMPTY} ,
    };
}

const std::vector<char> xo = {'X' , 'O', ' '};

void GameController::printMatchfield() {
    for(std::vector<Field> row : match_field) {
        std::cout << "|";
        for(Field field : row) {
            std::cout << " " << xo[field] << " |" ; 
        }
        std::cout << std::endl;
    }
}

void GameController::getUserInput() {
    while(true) {
        std::cout << "Where do you want to put the cross ?" << std::endl;
        std::cout << "-----> Input format: <row>,<column>, e.g, '2,0'" << std::endl;
        std::string position;
        std::cin >> position;
        
        bool invalid = false;
        if(position.length() != 3) {
            std::cout << "!!! Invalid input. Please try again !!!" << std::endl;
        }
        else {
            int x = 0, y = 0;
            if(position[0] >= '0' && position[0] <= '2') {
                y = position[0] - '0';
            }
            else {
                std::cout << position[0] << position << std::endl;
                std::cout << "!!! Invalid row position. Please try again !!!" << std::endl;
            }

            if(position[2] >= '0' && position[2] <= '2') {
                x = position[2] - '0';
            }
            else {
                std::cout << position[2] << std::endl;
                std::cout << "!!! Invalid column position. Please try again !!!" << std::endl;
            }
            if(this->match_field[y][x] == Field::EMPTY) {
                this->match_field[y][x] = Field::CROSS;
                std::cout << "~~~ Done ~~~" << std::endl;
                break;
            }
            else {
                std::cout << "!!! The field is already occupied !!!" << std::endl;
            }
        }
    }
}

std::optional<GameStatus> GameController::whoWon() const {
    std::vector<std::vector<std::vector<int>>> toChecks = {
        {{0, 0}, {0, 1}, {0, 2}}, {{1, 0}, {1, 1}, {1, 2}}, 
        {{2, 0}, {2, 1}, {2, 2}}, {{0, 0}, {1, 0}, {2, 0}},
        {{0, 1}, {1, 1}, {2, 1}}, {{0, 2}, {1, 2}, {2, 2}},
        {{0, 0}, {1, 1}, {2, 2}}, {{0, 2}, {1, 1}, {2, 0}},
    };

    bool full = true;
    for(std::vector<std::vector<int>> check : toChecks) {
        const Field& field = this->match_field[check[0][0]][check[0][1]];
        if(field == Field::EMPTY) {
            full = false;
            continue;
        }
        int count = 0;
        for(int i=0; i<3; i++) {
            const Field& curField = this->match_field[check[i][0]][check[i][1]];
            if(curField == Field::EMPTY) {
                full = false;
                continue;
            }
            count += curField == field? 1 : 0;
        }
        if(count == 3) {
            return field == Field::CROSS ? std::optional<GameStatus>(GameStatus::USER) : std::optional<GameStatus>(GameStatus::COMPUTER);
        }
    }

    if(full) return std::optional<GameStatus>(GameStatus::TIE); 
    else return std::optional<GameStatus>();
}

void GameController::play() {
    bool isHumanTurn = rand()%2==0;

    bool running = true;
    while(running) {
        std::cout << "============================= START GAME ==============================" << std::endl;
        while(true) {
            this->printMatchfield();
            if(isHumanTurn) {
                std::cout << "------- You are in turn! Make your move :) -------" << std::endl;
                this->getUserInput();
            }
            else {
                std::cout << "--------------- BOT is in turn! :/ ---------------" << std::endl;
                this->calulateNextMove();
            }
            isHumanTurn = !isHumanTurn;
            
            std::optional<GameStatus> gameStatus = this->whoWon();

            if(gameStatus.has_value()) {

                this->printMatchfield();

                GameStatus& status = gameStatus.value();
                if(status == GameStatus::USER) {
                    std::cout << ">>>>>>>>>>> You win the game! <<<<<<<<<<<<<<<" << std::endl;
                }
                else if(status == GameStatus::COMPUTER) {
                    std::cout << ">>>>>>>>>>> BOT wins the game! <<<<<<<<<<<<<" << std::endl;
                }
                else {
                    std::cout << ">>>>>>>>>>> Tie! Well played <<<<<<<<<<<<<" << std::endl;
                }
                break;
            } 
        }

        std::cout << "============================= END GAME ==============================" << std::endl;
        char c;
        while(true) {
            std::cout << "********** Do you want to retry? (y/n) **********" << std::endl;
            std::cin >> c;
            if(c == 'n') {
                running = false;
                break;
            }
            else if(c == 'y') {
                for(std::vector<Field>& row : this->match_field) {
                    for(int i=0; i<3; i++) {
                        row[i] = Field::EMPTY;
                    }
                }
                break;
            }
            else {
                std::cout << "!!! Your input is invalid! The input should just be y/n !!!" << std::endl;
            }
        }
    }
}