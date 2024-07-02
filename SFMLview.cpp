//
// Created by dawid on 12.05.22.
//

#include "SFMLview.h"
#include <vector>
#include <iostream>
SFMLview::SFMLview(Snake &s, SFMLcontroller &c) : snake(s), ctrl(c){
    if(!fontA.loadFromFile("../font/Coffee Extra.ttf"))
        abort();
    if(!fontB.loadFromFile("../font/GothicA1-Black.ttf"))
        abort();

    //Menu
    text_snake = {"Snake", fontA, 100};
    text_snake.setFillColor(sf::Color{38, 77, 0});
    text_snake.setPosition(310,50);
    text_difficulty = {"",fontA, 50};
    text_difficulty.setFillColor(sf::Color::Black);
    difficulty.setSize({400,100});
    difficulty.setFillColor(sf::Color{38, 77, 0});
    difficulty.setOutlineThickness(3);

    //Game
    body_snake.setSize({19,19});
    body_snake.setFillColor(sf::Color{38, 77, 0});
    body_snake.setOutlineThickness(1);
    body_snake.setOutlineColor(sf::Color::Black);
    feed.setSize({19,19});
    feed.setFillColor(sf::Color{230, 184, 0});
    feed.setOutlineThickness(1);
    feed.setOutlineColor(sf::Color::Black);
    border.setSize({19,19});
    border.setFillColor(sf::Color{102, 0, 0});
    border.setOutlineThickness(1);
    border.setOutlineColor(sf::Color::Black);
    text_current_score = {"SCORE: ", fontB, 30};
    text_current_score.setFillColor(sf::Color{38, 77, 0});
    text_current_score.setPosition(360, 610);
    current_score = {"", fontB, 30};
    current_score.setFillColor(sf::Color{38, 77, 0});
    current_score.setPosition(490, 610);

    //Input name
    text_name = {"\t\t\t\t\t\t\tGratulacje! \nUzyskales wynik dajacy miejsce w top 10!\n \t\t\t\t\tPodaj swoje imie:", fontB, 40 };
    text_name.setFillColor(sf::Color::White);
    text_name.setPosition(50,120);
    text_input_name = {"", fontB, 35};
    text_input_name.setFillColor(sf::Color::White);
    input_name.setSize({500,100});
    input_name.setFillColor(sf::Color{38, 77, 0});
    input_name.setPosition(200,300);
    input_name.setOutlineThickness(5);
    input_name.setOutlineColor(sf::Color{20, 38, 0});
    button.setSize({200,60});
    button.setFillColor(sf::Color{38, 77, 0});
    button.setOutlineThickness(5);
    button.setOutlineColor(sf::Color{20, 38, 0});
    text_button = {"Kontynuuj", fontB, 20};
    text_button.setFillColor(sf::Color::White);
    text_yourscore = {"", fontB, 40};
    text_yourscore.setFillColor(sf::Color{38, 77, 0});

    //Score Board
    text_scoreBoard = {"SCORE BOARD", fontB, 50};
    text_scoreBoard.setFillColor(sf::Color{38, 77, 0});
    text_scoreBoard.setPosition(260, 30);
    text_score = {"", fontB, 25};
    text_score.setFillColor(sf::Color::White);
    text_score.setPosition(370, 110);
    button_reset.setSize({300, 100});
    button_reset.setFillColor(sf::Color{38, 77, 0});
    button_reset.setPosition(300, 500);
    button_reset.setOutlineThickness(4);
    button_reset.setOutlineColor(sf::Color{20, 38, 0});
    text_reset = {"RESTART", fontB, 30};
    text_reset.setFillColor(sf::Color::White);
    text_reset.setPosition(380,530);
}

void SFMLview::draw(sf::RenderWindow &win) {
    std::vector<sf::Vector2i> position = snake.get_snake();
    std::vector<sf::Vector2i> food = snake.get_food();
    text_score.setString("");

    //food
    for (size_t element = 0; element < food.size(); element++) {
        feed.setPosition(food[element].x * 20, food[element].y * 20);
        win.draw(feed);
    }

    //snake
    for (size_t part = 0; part < position.size(); part++) {
        if (part == position.size() - 1) {
            body_snake.setFillColor(sf::Color{20, 38, 0});
            body_snake.setPosition(position[part].x * 20, position[part].y * 20);
            win.draw(body_snake);
        } else {
            body_snake.setFillColor(sf::Color{38, 77, 0});
            body_snake.setPosition(position[part].x * 20, position[part].y * 20);
            win.draw(body_snake);
        }
    }

    //border
    for (int row = 0; row < 30; row++) {
        if (row == 0 || row == 29) {
            for (int col = 0; col < 45; col++) {
                border.setPosition(col * 20, row * 20);
                win.draw(border);
            }
        } else {
            border.setPosition(0, row * 20);
            win.draw(border);
            border.setPosition(880, row * 20);
            win.draw(border);
        }
    }

    //score
    current_score.setString(std::to_string(snake.get_score()));
    win.draw(text_current_score);
    win.draw(current_score);
}

void SFMLview::drawMenu(sf::RenderWindow &win) {
    //Title
    win.draw(text_snake);

    //Buttons
    difficulty.setOutlineColor(sf::Color::Green);
    difficulty.setPosition({250,200});
    win.draw(difficulty);

    difficulty.setOutlineColor(sf::Color::Yellow);
    difficulty.setPosition({250,320});
    win.draw(difficulty);

    difficulty.setOutlineColor(sf::Color::Red);
    difficulty.setPosition({250,440});
    win.draw(difficulty);

    //Labels
    text_difficulty.setPosition({395,215});
    text_difficulty.setString("Easy");
    win.draw(text_difficulty);

    text_difficulty.setPosition({365,335});
    text_difficulty.setString("Normal");
    win.draw(text_difficulty);

    text_difficulty.setPosition({395,455});
    text_difficulty.setString("Hard");
    win.draw(text_difficulty);
}

void SFMLview::drawInputName(sf::RenderWindow &win) {
    text_yourscore.setString("Twoj wynik to: " + std::to_string(snake.get_score()));

    if(snake.check_score()) {
        text_yourscore.setPosition(250, 35);
        button.setPosition(350,450);
        text_button.setPosition(400, 467);
        text_input_name.setPosition(435 - (ctrl.getName().getSize() * 10), 325);\
        text_input_name.setString(ctrl.getName());
        win.draw(text_yourscore);
        win.draw(text_name);
        win.draw(input_name);
        win.draw(text_input_name);
        win.draw(button);
        win.draw(text_button);
    }
    else{
        button.setPosition(350,400);
        text_button.setPosition(400, 417);
        text_yourscore.setPosition(250,150);
        win.draw(text_yourscore);
        win.draw(button);
        win.draw(text_button);
    }
}

void SFMLview::drawScoreBoard(sf::RenderWindow &win) {
    if(text_score.getString() == "")
        readScore();

    win.draw(text_scoreBoard);
    win.draw(text_score);
    win.draw(button_reset);
    win.draw(text_reset);
}

void SFMLview::readScore() {
    score.open("../score/score.txt", std::ios::in);
    if (score.good())
    {
        while(std::getline(score, record)) {
            text_score.setString(text_score.getString() + record + "\n");
        }
    }
    score.close();
}