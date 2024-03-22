#include <SFML/Graphics.hpp>

#include "headers/LetterBlock.hpp"
#include "headers/MainGame.hpp"

int main(int argc, char const* argv[]) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Hello From SFML");

    // MainGame game;
    // game.window = sf::RenderWindow(sf::VideoMode(1920,1080),"test");

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
        shape.move(sf::Vector2f(10, 10));
        test.setColor(sf::Color::Red);
        test.display(true);
    }

    return 0;
}
