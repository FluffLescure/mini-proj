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
    sf::RenderWindow *window;

    // map that stores the game layout built in sf::Quads
    sf::VertexArray layout;

    // Agregated classes
    Input *input;
    GameGrid *game;
    GameScore *score;
    GameLogs *logs;
    GameLetter *next;
    GameLevel *level;

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
    * @brief Frees GameGrid from memory 
    */
    ~MainGame();


    /**
     * @brief Determines if the gam is running based on the state of the window
    */
    bool isRunning();


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


    

    
};

#endif