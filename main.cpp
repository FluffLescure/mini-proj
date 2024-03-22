#include <SFML/Graphics.hpp>

#include "headers/LetterBlock.hpp"
#include "headers/MainGame.hpp"

int main(int argc, char const* argv[]) {

    MainGame game;

    sf::RectangleShape backgrid(sf::Vector2f(311,486));
    backgrid.setFillColor(sf::Color::Red);
    backgrid.setOutlineColor(sf::Color::Blue);
    backgrid.setOutlineThickness(2);
    backgrid.setPosition(sf::Vector2f(325,27));

    sf::RectangleShape background(sf::Vector2f(960,540));
    background.setFillColor(sf::Color(100,100,100,255));
    background.setOutlineColor(sf::Color::Blue);
    background.setOutlineThickness(2);

    LetterBlock block("A");
    block.setColor(sf::Color::Cyan);


    while (game.window.isOpen()) {
        sf::Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                game.window.close();
            }
        }   
        game.window.clear();

        game.window.draw(background);

        game.window.draw(backgrid);

        game.window.draw(block.getBlock());
        block.fetchBlock().setPosition(325,27);
        sf::Text letter;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        letter.setString(block.getLetter());
        letter.setFont(font);
        letter.setCharacterSize(20);
        letter.setFillColor(sf::Color::Magenta);
        letter.setOrigin(340,42);
        game.window.draw(letter);

        game.window.display();
       
    }

    return 0;
}
