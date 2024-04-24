
#include <SFML/Window/Keyboard.hpp>

#include "../headers/Input.hpp"


void Input::pollEvent() {
    // Directions respectfully stored from input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = Down;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = Left;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = Right;

    if(direction != Direction::Unchanged)
        inputTick();
}

int Input::inputTick(bool keepTicking) {
    static int inputTick = 0;

    if(!keepTicking)
        return inputTick;

    if(inputTick != 5){
        inputTick++;
        return inputTick;     
    }

    direction = Direction::Unchanged;
    inputTick = 0;
    return 0;
}