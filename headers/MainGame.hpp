#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


#include "GameGrid.hpp"
#include "GameLogs.hpp"

/**
* @class MainGame
* @brief Used to display the different blokc of the game layout
*
* @remark The class' main function is to display and update each 
* layout block with an aggregation link and through methods render() 
* and update(). The update() method is used for back-end changes
* while render() will exclusively be used to render drawables to 
* window.
*/
class MainGame: sf::NonCopyable {
private:
    sf::RenderWindow *window;
    // map that stores the layout, built in sf::Quads
    sf::VertexArray layout;
    // aggregation link to GameGrid
    GameGrid *game;
    GameLogs *logs;

public:
    /**
    * @brief Constructor that links to GameGrid and initialises layout
    */
    MainGame();

    /**
    * @brief Frees GameGrid from memory 
    */
    ~MainGame();

    /**
    * @brief Initialises the layout using preloaded resources from Config 
    */
    void initLayout();

    /**
     * @brief Initialises the game window
    */
    void initWindow();

    bool isRunning();

    void run();

    void pollEvent();


    /**
    * @brief Renders blocks and layout of the game 
    * @param *target the renderer shared to other classes
    */
    void render();

    /**
    * @brief calls for update of the logic and states of each class 
    */
    void update();
};

#endif