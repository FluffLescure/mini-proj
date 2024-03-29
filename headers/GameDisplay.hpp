#ifndef GAME_DISPLAY_HPP
#define GAME_DISPLAY_HPP

#include <SFML/Graphics.hpp>

#include "GameGrid.hpp"
#include "Config.hpp"

/**
* @class GameDisplay
* @brief Used to display the different blokc of the game layout
*
* @remark The class' main function is to display and update each 
* layout block with an aggregation link and through methods render() 
* and update()
*
*/
class GameDisplay {
private:
    // map that stores the layout, built in sf::Quads
    sf::VertexArray layout;
    // aggregation link to GameGrid
    GameGrid *game;

public:
    /**
    * @brief Constructor that links to GameGrid and initialises layout
    */
    GameDisplay();

    /**
    * @brief Frees GameGrid from memory 
    */
    ~GameDisplay();

    /**
    * @brief Initialises the layout using preloaded resources from Config 
    */
    void initLayout();

    /**
    * @brief Renders blocks and layout of the game 
    * @param *target the renderer shared with other classes
    */
    void render(sf::RenderTarget *target);

    /**
    * @brief calls for update of the logic and states of each class 
    */
    void update();
};

#endif