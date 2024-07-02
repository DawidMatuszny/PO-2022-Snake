//
// Created by dawid on 05.05.22.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "SFML/Graphics.hpp"
#include <vector>
#include <fstream>

enum GameState { RUNNING, SCOREBOARD, FINISHED, MENU};
enum GameMode {EASY, NORMAL, HARD};

struct ScoreBoard{
    int score;
    std::string name;
};

class Snake {
    std::vector <sf::Vector2i> snake;
    sf::Vector2i direction;
    GameState state;
    GameMode mode;
    std::vector <sf::Vector2i> food;
    int snakeSpeed, score;
    sf::Clock clock_move, clock_food;
    std::string input_direction;
    std::fstream dataScore;
    ScoreBoard sc_board[10];
public:
    Snake();
    void turn(std::string turn_direction);
    void move();
    void update();
    bool check_collision();
    void add_food();
    bool check_eaten();
    void init_empty_score();
    void read_records();
    int check_score() const;
    void reset_game();
    void save_record(std::string name);
    void set_input_direction(std::string turn_direction);
    void set_state(GameState gstate);
    void set_mode(GameMode gmode);
    GameState get_state() const;
    std::vector <sf::Vector2i> get_snake() const;
    std::vector <sf::Vector2i> get_food() const;
    sf::Vector2i get_direction() const;
    int get_score() const;
};


#endif //SNAKE_SNAKE_H
