#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


#include "GameGrid.hpp"
#include "Config.hpp"
#include "Input.hpp"
#include "GameLogs.hpp"
#include "GameScore.hpp"
#include "GameLetter.hpp"
#include "GameLevel.hpp"

/**
* @class MainGame
* @brief Used to display the different blokc of the game layout
*
* @remark The class' main function is to display and update each 
* layout block with an aggregation link and through methods render() 
* and update().
* The update() method is used for back-end changes while render() will
* exclusively be used to render drawables to window.
*/
class MainGame: sf::NonCopyable {
private:
    sf::RenderWindow *window_;

    // map that stores the game layout built in sf::Quads
    sf::VertexArray layout_;

    // Game over message
    sf::Text over_;

    // Agregated classes
    Input *input_;
    GameGrid *game_;
    GameScore *score_;
    GameLogs *logs_;
    GameLetter *next_;
    GameLevel *level_;

public:
    /**
    * @brief Constructor that links to GameGrid and initialises layout
    */
    MainGame();

    /**
    * @brief Initialises the layout using preloaded resources from Config 
    */
    void initLayout();

    /**
     * @brief Initialises the game window
    */
    void initWindow();

    /**
     * @brief initalises game components
    */
    void initComponents();

    /**
     * @brief Initialises the game over message
    */
    void initOver();


    /**
    * @brief Frees GameGrid from memory 
    */
    ~MainGame();


    /**
     * @brief Determines if the game is running based on the state of the window
    */
    const bool isRunning();


    /**
     * @brief Runs the main instance of the game
    */
    void run();

    /**
    * @brief Renders the game
    */
    void render();

    /**
    * @brief Calls for the update of game logic with tick dependent timing
    */
    void update();

    /**
     * @brief Retrieves events related to the game window
    */
    void pollEvent();

    /**
     * @brief Displays a game over message and offers a restart.
     * @param input The input to restart the game
    */
    void GameOver(const Direction& input);

};

#endif