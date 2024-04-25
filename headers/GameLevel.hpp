#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include<map>
#include<string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


/**
 * @class GameLevel
 * @brief A class that manages the level and stage of the game
 * @remark It will also change the color scheme based on the stage
 * 
 * @code
 * GameLevel level = GameLevel();
 * 
 * // Renders the level and stage components
 * level.render(window);
 * 
 * // Increases the level and stage of the game
 * level.levelUp();
 * 
 * // Gets the speed of the game
 * int speed = level.getSpeed();
 * @endcode
*/
class GameLevel {
private:
    // The tick speed of the game
    int speed;

    // Color Schemes
    std::map<std::string, sf::Color> colorScheme[4];

    // Frame Components
    sf::RectangleShape stageFrame;
    sf::RectangleShape levelFrame;

    // Text Components
    sf::Text levelText;
    sf::Text stageText;

public:

    /**
     * @brief Constructor which call initialisation of components
    */
    GameLevel();

    /**
     * @brief Initialises the color schemes
    */
    constexpr void initColorschemes();

    /**
     * @brief Initialises the frame components
    */
    constexpr void initFrames();

    /**
     * @brief Initialises the text components
    */
    constexpr void initText();
    
    /**
     * @brief A getter function for the speed of the game
     * @brief Returns the current speed
    */
    constexpr const int getSpeed() const { return speed; }

    /**
     * @brief Increases the level of the game and, if required, the stage
    */
    void levelUp();

    /**
     * @brief Renders the level's bounding frame and text components
     * @param *target the rendered shared by other classes
    */
    void render(sf::RenderTarget *target) const;

};



#endif