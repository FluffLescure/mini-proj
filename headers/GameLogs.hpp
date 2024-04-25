#ifndef GAME_LOGS_HPP
#define GAME_LOGS_HPP


#include<vector>
#include<string>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "LetterBlock.hpp"


/**
 * @class GameLogs
 * 
 * @brief Logs showing the previously made words and their attributed scores
 *  in separate columns
 * 
 * @remark the points column will have left alignement, and both columns will
 *  be limited to a maximum of 10 elements 
 * 
 * @code
 * GameLogs logs = GameLogs();          // init of components with empty logs
 * logs->emplace("new text");           // text placed to top with corresponding score
 * logs->emplaceLog("newer text");      // text placed to top without updating score
 * logs->emplacePoints("newest text")   // score of text placed to top without text update
 * @endcode
 */
class GameLogs {
private:

    // Border used to draw the grid frame
    sf::RectangleShape logsFrame;

    // Text componnents
    sf::Text title;
    sf::Text logs[10];
    sf::Text points[10];

public:

    /**
     * @brief Constructor which calls initilisation of components
    */
    GameLogs();

    /**
     * @brief Draws the frame of the object
    */
    constexpr void initFrame();

    /**
     * @brief Initiliases the title text
    */
    constexpr void initTitle();

    /**
     * @brief Initialises the logs column of the display
    */
    constexpr void initLogs();

    /**
     * @brief Initialises the points column of the display
    */
    constexpr void initPoints();


    /**
     * @brief Places the word and its score to the top of the logs
     * @param word the word to be logged
    */
    void emplace(std::string word);

    /**
     * @brief Places the word to the top of the logs
     * @param word the word to be logged
    */
    constexpr void emplaceLog(std::string word);

    /**
     * @brief Places the word score to the top of the logs
     * @param word the word to be logged
    */
    constexpr void emplacePoints(std::string word);


    /**
     * @brief Renders the log's bounding frame and text components
     * @param *target the rendered shared by other classes
    */
    void render(sf::RenderTarget *target) const;

};

#endif