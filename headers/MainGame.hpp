
#ifndef MAIN_GAME_HPP
#define MAIN_GAME_HPP

#include <SFML/Graphics.hpp>
#include "GameDisplay.hpp"
#include "Config.hpp"

class MainGame : sf::NonCopyable {

public:
    sf::RenderWindow *window;
    GameDisplay *layout;

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
