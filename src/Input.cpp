
#include <SFML/Window/Keyboard.hpp>

#include "../headers/Input.hpp"


void Input::pollEvent() {
    // Directions respectfully stored from input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = Down;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = Left;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = Right;

    if(direction != Direction::Unchanged)
        pressTick();
}

int Input::pressTick(bool keepTicking) {
    static int pressTick = 0;

    if(!keepTicking)
        return pressTick;

    if(pressTick != 5){
        pressTick++;
        return pressTick;     
    }

    direction = Direction::Unchanged;
    pressTick = 0;
    return 0;
}