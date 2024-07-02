//
// Created by Dawid on 2022-05-16.
//

#include "SFMLcontroller.h"


SFMLcontroller::SFMLcontroller(Snake &s) :snake(s) {}

void SFMLcontroller::eventLoop(sf::Event &event) {

    //Menu operation
    if (snake.get_state() == MENU && event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.x > 250 && event.mouseButton.x < 650){
            if (event.mouseButton.y > 200 && event.mouseButton.y < 300){
                snake.set_mode(EASY);
                snake.set_state(RUNNING);
            }
            if (event.mouseButton.y > 320 && event.mouseButton.y < 420){
                snake.set_mode(NORMAL);
                snake.set_state(RUNNING);
            }
            if (event.mouseButton.y > 440 && event.mouseButton.y < 540){
                snake.set_mode(HARD);
                snake.set_state(RUNNING);
            }
        }
    }


    //Control snake
    if (snake.get_state() == RUNNING && event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Left) {
            if (snake.get_direction().x == 0) {
                if (snake.get_direction().y == 1)
                    snake.set_input_direction("right");
                if (snake.get_direction().y == -1)
                    snake.set_input_direction("left");
            }
        }
        if (event.key.code == sf::Keyboard::Right) {
            if (snake.get_direction().x == 0) {
                if (snake.get_direction().y == 1)
                    snake.set_input_direction("left");
                if (snake.get_direction().y == -1)
                    snake.set_input_direction("right");
            }
        }
        if (event.key.code == sf::Keyboard::Up) {
            if (snake.get_direction().y == 0) {
                if (snake.get_direction().x == 1)
                    snake.set_input_direction("left");
                if (snake.get_direction().x == -1)
                    snake.set_input_direction("right");
            }
        }
        if (event.key.code == sf::Keyboard::Down) {
            if (snake.get_direction().y == 0) {
                if (snake.get_direction().x == 1)
                    snake.set_input_direction("right");
                if (snake.get_direction().x == -1)
                    snake.set_input_direction("left");
            }
        }
    }

    //Score Board
    if (snake.get_state() == SCOREBOARD && event.type == sf::Event::MouseButtonPressed){
        if (event.mouseButton.x > 300 && event.mouseButton.x < 600 && event.mouseButton.y > 500 && event.mouseButton.y < 600) {
            snake.reset_game();
            snake.set_state(MENU);
        }
    }

    //Input Name
    if (snake.check_score()) {
        if (snake.get_state() == FINISHED && event.type == sf::Event::TextEntered) {
            if ((event.text.unicode >= 65 && event.text.unicode <= 90) || (event.text.unicode >= 97 && event.text.unicode <= 122))
                name += event.text.unicode;
        }
        if (snake.get_state() == FINISHED && event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.x > 350 && event.mouseButton.x < 550 && event.mouseButton.y > 450 &&
                event.mouseButton.y < 510) {
                snake.save_record(name);
                snake.set_state(SCOREBOARD);
                name.clear();
            }
        }
    }
    if (!snake.check_score()){
        if (snake.get_state() == FINISHED && event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.x > 350 && event.mouseButton.x < 550 && event.mouseButton.y > 400 &&
                event.mouseButton.y < 460)
                snake.set_state(SCOREBOARD);

        }
    }
}

sf::String SFMLcontroller::getName() {
    return name;
}