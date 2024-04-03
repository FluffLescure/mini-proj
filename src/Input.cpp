
#include <SFML/Window/Keyboard.hpp>

#include "../headers/Input.hpp"


void Input::pollEvent() {
    direction = Direction::Unchanged;
    // Directions respectfully stored from input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = Down;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = Left;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = Right;
}
