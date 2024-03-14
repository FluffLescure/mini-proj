#include <SFML/Graphics.hpp>

#include "lib/LetterBlock.hpp"

int main(int argc, char const* argv[]) {
    sf::RenderWindow window(sf::VideoMode(1920, 1800), "Hello From SFML");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Magenta);
    LetterBlock test;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.draw(test.getBlock());
        window.display();
        test.setColor(sf::Color::Red);
        test.display(true);
    }

    return 0;
}
