
#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include <SFML/Graphics.hpp>
#include "GameDisplay.hpp"

class MainGame : sf::NonCopyable {
public:
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(960,540),"Lettris");

};

#endif
