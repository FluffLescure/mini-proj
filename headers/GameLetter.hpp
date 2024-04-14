#ifndef GAME_LETTER_HPP
#define GAME_LETTER_HPP



#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "LetterBlock.hpp"


/**
 * @class GameLetter
 * 
 * @brief Shows the next letter 
 * 
 * 
 * 
 */
class GameLetter : sf::NonCopyable {
private:

    // Border used to draw the grid frame
    sf::RectangleShape letterFrame;
    sf::Text title;
    sf::Text letter;


public:
    GameLetter();

    void initFrame();
    void initTitle();
    void initLetter();



    void changeLetter(char newLetter);

    /**
     * @brief Renders the grid's bounding frame and the 2D game grid
     * @param *target the rendered shared to other classes
    */
    void render(sf::RenderTarget *target);

};

#endif