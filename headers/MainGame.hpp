
#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include <SFML/Graphics.hpp>

class MainGame : sf::NonCopyable {
public:
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920,1080),"Lettris");

    MainGame() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed) 
                    window.close();
        }
    }
};

#endif
