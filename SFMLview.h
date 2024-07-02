//
// Created by dawid on 12.05.22.
//

#ifndef SNAKE_SFMLVIEW_H
#define SNAKE_SFMLVIEW_H

#include <fstream>
#include "Snake.h"
#include "SFML/Graphics.hpp"
#include "SFMLcontroller.h"

class SFMLview {
    Snake &snake;
    SFMLcontroller &ctrl;
    sf::Font fontA, fontB;
    sf::RectangleShape difficulty, input_name, button, feed, body_snake, border, button_reset;
    sf::Text text_difficulty, text_snake, text_scoreBoard, text_score, text_input_name, text_name, text_button;
    sf::Text text_current_score, current_score, text_reset, text_yourscore;
    std::fstream score;
    std::string record;
public:
    SFMLview(Snake &s, SFMLcontroller &c);
    void draw(sf::RenderWindow &win);
    void drawMenu(sf::RenderWindow &win);
    void drawScoreBoard(sf::RenderWindow &win);
    void drawInputName(sf::RenderWindow &win);
    void readScore();
};


#endif //SNAKE_SFMLVIEW_H
