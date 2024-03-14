#ifndef LETTER_BLOCK_HPP
#define LETTER_BLOCK_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class LetterBlock {
private:
    sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(100, 100));
    char letter;

public:
    void setColor(sf::Color color) { block.setFillColor(color); }
    char getLetter() const { return letter; }
};

#endif