#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include<map>
#include<string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

/**
 * @author Lucas Lescure
 * @class GameLevel
 * 
 * @brief A class that manages the level and stage of the game
 * 
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
    int speed_;

    //Color Schemes
    std::map<std::string, sf::Color> colorScheme_[4];

    // Frame components
    sf::RectangleShape stageFrame_;
    sf::RectangleShape levelFrame_;

    // Text components
    sf::Text levelText_;
    sf::Text stageText_;

public:

    /**
     * @brief Constructor which call initialisation of components
    */
    GameLevel();

    /**
     * @brief Initialises the color schemes
    */
    void initColorschemes();

    /**
     * @brief Initialises the frame components
    */
    void initFrames();

    /**
     * @brief Initialises the text components
    */
    void initText();


    /**
     * @brief A getter function for the speed of the game
     * @return The current speed 
    */
    const int& getSpeed() const { return speed_; }


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