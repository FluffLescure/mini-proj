
#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include <SFML/Graphics.hpp>
#include "GameDisplay.hpp"

class MainGame : sf::NonCopyable {
public:
    sf::RenderWindow *window;
    GameDisplay *layout;
    sf::Font *font;

    MainGame();

    void initWindow();
    void initFont();
    void initInterface();

    void pollEvent();

    bool isRunning();

    void render();

    void run();



};

#endif
