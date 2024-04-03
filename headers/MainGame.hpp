
#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameDisplay.hpp"

class MainGame : sf::NonCopyable {

public:
    sf::RenderWindow *window;
    GameDisplay *display;

    MainGame();
    ~MainGame();

    void initWindow();
    void initInterface();

    void pollEvent();

    bool isRunning();

    void render();
    void update();

    void run();



};

#endif
