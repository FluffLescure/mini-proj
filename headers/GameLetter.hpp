#ifndef GAME_LETTER_HPP
#define GAME_LETTER_HPP


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "LetterBlock.hpp"


/**
 * @class GameLetter
 * 
 * @brief Randomizes the next falling letter and displays it on the game layout.
 * The letter will then be retrieved by the grid in which case a new letter is then 
 * loaded.  
 * 
 * 
 * 
 */
class GameLetter {
private:

    // Border used to draw the frame
    sf::RectangleShape letterFrame;

    //Tittle and letter text attributes
    sf::Text title;
    sf::Text letter;


public:
    
    /**
     * @brief Constructor which calls the initialisation of components
    */
    GameLetter();

    /**
     * @brief Draws the frame of the object
    */
    void initFrame();

    /**
     * @brief Initiliases the title text
    */
    void initTitle();

    /**
     * @brief Initialises the next letter text
    */
    void initLetter();


    /**
     * @brief Renders the object's bounding frame and its text
     * @param *target the rendered shared to other classes
    */
    void render(sf::RenderTarget *target);


    /**
     * @brief A simple getter function
     * @return The letter displayed
    */
    char getLetter();


    /**
     * @brief Changes the letter that is displayed
    */
    void changeLetter();
    
    /**
     * @brief The weighed randomiser which creates the new letter to be displayed
     * @return A randomised character between A and Z
    */
    char randLetter();

    

   

};

#endif