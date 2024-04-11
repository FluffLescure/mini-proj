#ifndef GAME_LOGS_HPP
#define GAME_LOGS_HPP



#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "LetterBlock.hpp"

#include "GameScore.hpp" 


/**
 * @class GameLogs
 * 
 * @brief Logs showing the previously made words and their attributed scores
 * 
 * 
 * 
 * 
 */
class GameLogs : sf::NonCopyable {
private:

    // Border used to draw the grid frame
    sf::RectangleShape logsFrame;
    sf::Text title;
    std::vector<sf::Text> logs;
    std::vector<sf::Text> points;

    GameScore* score;


public:
    GameLogs();

    void initFrame();
    void initTitle();
    void initLogs();
    void initPoints();

    void emplaceLog(std::string word);

    void emplacePoints(std::string word);

    /**
     * @brief Renders the grid's bounding frame and the 2D game grid
     * @param *target the rendered shared to other classes
    */
    void render(sf::RenderTarget *target);

};

#endif