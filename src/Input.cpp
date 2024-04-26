


#include <SFML/Window/Keyboard.hpp>

#include "../headers/Input.hpp"


void Input::pollEvent() {
    // Directions respectfully stored from input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) input_ = Down;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) input_ = Left;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) input_ = Right;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) input_ = Space;

    if(input_ != Direction::Unchanged)
        inputTick();
}

const int Input::inputTick(const bool& keepTicking) {
    static unsigned char inputTick = 0;

    // Returns the value of the counter if it is not supposed to keep ticking
    if(!keepTicking)
        return inputTick;

    // If the input is space then the counter ticks for 30 ticks
    if(input_ == Direction::Space && inputTick != 30){
        inputTick++;
        return inputTick;
    }

    // By default the counter ticks for 5 ticks (the length of a block tick)
    if(inputTick != 5) {
        inputTick++;
        return inputTick;
    }    
    
    // Resets the input and the counter
    input_ = Direction::Unchanged;
    return inputTick = 0;
}