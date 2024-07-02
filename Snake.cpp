//
// Created by dawid on 05.05.22.
//

#include "Snake.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Snake::Snake(){
    srand(time(nullptr));
    state = MENU;
    init_empty_score();
    reset_game();
}


void Snake::move() {
    snake.erase(snake.begin());
    snake.push_back(snake[snake.size()] + direction);
}

void Snake::update(){
    if(state == RUNNING && clock_move.getElapsedTime().asMilliseconds() > snakeSpeed/((mode+1)*2)) {
        turn(input_direction);
        check_collision();
        if(!check_eaten())
            move();
        add_food();
        clock_move.restart();
        input_direction = "";
    }
}

bool Snake::check_collision() {
    for(size_t part = 0; part < snake.size()-1; part++)
    {
        if(snake[part] == snake[snake.size()-1] + direction) {
            state = FINISHED;
            return true;
        }
    }
    if(snake[snake.size()-1].x == 0 || snake[snake.size()-1].x == 44
    || snake[snake.size()-1].y == 0 || snake[snake.size()-1].y == 29){
        state = FINISHED;
        return true;
    }
    return false;
}

void Snake::turn(std::string turn_direction){
    if(turn_direction == "left"){
        if(direction.x == 0){
            if(direction.y == 1)
                direction = {1,0};
            else
                direction = {-1,0};
        }
        else{
            if(direction.x == 1)
                direction = {0,-1};
            else
                direction = {0,1};
        }
    }
    if(turn_direction == "right"){
        if(direction.x == 0){
            if(direction.y == 1)
                direction = {-1,0};
            else
                direction = {1,0};
        }
        else{
            if(direction.x == 1)
                direction = {0,1};
            else
                direction = {0,-1};
        }
    }
}

void Snake::add_food() {
    if(state == RUNNING && clock_food.getElapsedTime().asMilliseconds() > 3000/(mode+1) && food.size() < 6) {
        int x_cord, y_cord;
        bool empty_place;
        do{
            empty_place = true;
            x_cord = (rand() % 43) + 1;
            y_cord = (rand() % 28) + 1;
            for(size_t part = 0; part < snake.size(); part++)
            {
                if(snake[part].x == x_cord && snake[part].y == y_cord)
                    empty_place =false;
            }
            for(size_t feed = 0; feed < food.size(); feed++)
            {
                if(food[feed].x == x_cord && food[feed].y == y_cord)
                    empty_place =false;
            }
        }while(!empty_place);
        food.push_back({x_cord, y_cord});
        clock_food.restart();
    }
}

bool Snake::check_eaten() {
    for(size_t feed = 0; feed < food.size(); feed++)
    {
        if(food[feed].x == snake[snake.size()-1].x && food[feed].y == snake[snake.size()-1].y)
        {
            food.erase(food.begin()+feed);
            score += 100 * (mode+1);
            snake.push_back(snake[snake.size()-1] + direction);
            return true;
        }
    }
    return false;
}

void Snake::read_records() {
    dataScore.open("../score/score.txt", std::ios::in);
    if (dataScore.good()) {
        int nrRecord = 0;
        while(!dataScore.eof()) {
            dataScore >> sc_board[nrRecord].score;
            dataScore >> sc_board[nrRecord].name;
            nrRecord++;
        }
    }
    dataScore.close();
}


int Snake::check_score() const {
    for(int nrRecord = 0; nrRecord < 10; nrRecord++){
        if (sc_board[nrRecord].score < score)
            return nrRecord+1;
    }
    return 0;
}

void Snake::save_record(std::string name) {
    if (name == "")
        name = "unnamed";
    dataScore.open("../score/score.txt", std::ios::out | std::ios::trunc);
    if (dataScore.good()) {
        int score_place = check_score();
        for (int nrRecord = 0; nrRecord < 10; nrRecord++) {
            if (nrRecord == score_place - 1)
                dataScore << score << "\t" << name << std::endl;
            if (sc_board[nrRecord].score != 0 && nrRecord < 9)
                dataScore << sc_board[nrRecord].score << "\t" << sc_board[nrRecord].name << std::endl;
            }
        }
    dataScore.close();
}


void Snake::init_empty_score() {
    for(int nrRecord = 0; nrRecord < 10; nrRecord++){
        sc_board[nrRecord] = {0, ""};
    }
}

void Snake::reset_game() {
    snake.clear();
    food.clear();
    snake.push_back({20,15});
    snake.push_back({21,15});
    snake.push_back({22,15});
    direction = {1,0};
    score = 0;
    snakeSpeed = 300;
    read_records();
}

std::vector <sf::Vector2i> Snake::get_snake() const {
    return snake;
}

sf::Vector2i Snake::get_direction() const {
    return direction;
}

std::vector <sf::Vector2i> Snake::get_food() const{
    return food;
}

GameState Snake::get_state() const {
    return state;
}

void Snake::set_input_direction(std::string turn_direction) {
    input_direction = turn_direction;
}

void Snake::set_state(GameState gstate) {
    state = gstate;
}

void Snake::set_mode(GameMode gmode) {
    mode = gmode;
}

int Snake::get_score() const{
    return score;
}