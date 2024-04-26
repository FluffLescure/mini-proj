#ifndef GAME_LETTER_HPP
#define GAME_LETTER_HPP


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "LetterBlock.hpp"


/**
 * @class GameLetter
 * 
 * @brief Randomises the next falling letter and displays it on the game layout.
 * The letter will then be retrieved by the grid in which case a new letter is then 
 * loaded.  
 * 
 * @remark The class alllows simple randomisation with getters and setters.
 * @code 
 * GameLetter next = GameLetter();  // init with random letter
 * 
 * char c = next->getLetter();      // retrieves current displayed letter
 * 
 * c = next->randLetter();          // returns a random letter;
 * 
 * next->changeLetter();            // randomises the display letter
 * @endcode
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
     * @brief Initialises the frame of the object
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
     * @param *target the rendered shared by other classes
    */
    void render(sf::RenderTarget *target) const;


    /**
     * @brief A simple getter function
     * @return The letter displayed
    */
    const char getLetter();


    /**
     * @brief Randomises and changes the letter that is displayed 
    */
    void changeLetter();
    
    /**
     * @brief The weighed randomiser which creates the new letter to be displayed
     * @return A randomised character between A and Z
    */
    const char randLetter();

    

   

};

#endif