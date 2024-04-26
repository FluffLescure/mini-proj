
#include <SFML/Window/Keyboard.hpp>

#include "../headers/Input.hpp"


void Input::pollEvent() {
    // Directions respectfully stored from input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) input = Down;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) input = Left;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) input = Right;

    if(input != Direction::Unchanged)
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

    input = Direction::Unchanged;
    inputTick = 0;
    return 0;
}