//
// Created by Dawid on 2022-05-16.
//

#ifndef SNAKE_SFMLCONTROLLER_H
#define SNAKE_SFMLCONTROLLER_H

#include "Snake.h"
#include "SFML/Graphics.hpp"

class SFMLcontroller {
    Snake &snake;
    sf::String name;
public:
    explicit SFMLcontroller(Snake &s);
    void eventLoop(sf::Event &event);
    sf::String getName();
};


#endif //SNAKE_SFMLCONTROLLER_H
