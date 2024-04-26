


#include <SFML/Window/Keyboard.hpp>

#include "../headers/Input.hpp"


void Input::pollEvent() {
    // Directions respectfully stored from input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) input = Down;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) input = Left;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) input = Right;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) input = Space;

    if(input != Direction::Unchanged)
        inputTick();
}

const int Input::inputTick(const bool& keepTicking) {
    static unsigned char inputTick = 0;

    // Returns the value of the counter if it is not supposed to keep ticking
    if(!keepTicking)
        return inputTick;

    // If the input is space then the counter ticks for 30 ticks
    if(input == Direction::Space && inputTick != 30){
        inputTick++;
        return inputTick;
    }

    // By default the counter ticks for 5 ticks (the length of a block tick)
    if(inputTick != 5) {
        inputTick++;
        return inputTick;
    }    
    
    // Resets the input and the counter
    input = Direction::Unchanged;
    return inputTick = 0;
}