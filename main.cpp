#include <iostream>
#include "Snake.h"
#include <vector>
#include "SFMLview.h"
#include "SFML/Graphics.hpp"
#include "SFMLcontroller.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(900,650), "Snake");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);
    Snake snake{};
    SFMLcontroller ctrl(snake);
    SFMLview view(snake, ctrl);
    std::string direction;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            ctrl.eventLoop(event);
        }
        snake.update();
        window.clear();
        if(snake.get_state() == MENU)
            view.drawMenu(window);
        if(snake.get_state() == RUNNING)
            view.draw(window);
        if(snake.get_state() == FINISHED)
            view.drawInputName(window);
        if(snake.get_state() == SCOREBOARD)
            view.drawScoreBoard(window);
        window.display();
    }
    return 0;
}
