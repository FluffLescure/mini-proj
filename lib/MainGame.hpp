
#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include <SFML/Graphics.hpp>

class MainGame : sf::NonCopyable {
public:
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920,1080),"Lettris");
};

#endif
