#ifndef LETTER_BLOCK_HPP
#define LETTER_BLOCK_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Input.hpp"


/**
* @enum State
* @brief Possible states of the LetterBlock: Falling, Grounded, Fixed
*/
enum State {
    Falling,
    Grounded,
    Fixed
};



/**
 * \class LetterBlock
 *
 * \brief Blocks containing letters which will be used by the grid to create
 * chunks
 *
 * \note The default set size is 33.2x32.6px as specified in Config.
 *
 * \remark AlLows for simple display operations such as hiding the block or changing
 * it's fill color.
 * \code
 * LetterBlock block();            // defaults to a 33.2x32.6px block whith a ' '
 *                                    character
 * block.setColor(sf::Color::Red); // fills the block in red
 * block.display(false);           // hides the block (alpha = 0)
 * \endcode
 *
 * Utilities such as get and fetch are provided to respectfully retrieve data or modify
 * the object attribute.
 * \code
 * LetterBlock block('A');                      // creates a 100x100px block containing
 *                                                 the letter 'A'
 * char letter = block.getLetter();             // copies the 'letter' attribute
 * letter = block.fetchLetter();                // references the 'letter' attribute
 * sf::RectangleShape rect = block.getBlock();  // copies the 'block' attribute
 * rect = block.fetchBlock();                   // references the 'block' attribute
 * \endcode
 *
 */
class LetterBlock {

    // Macro of a 2D grid of LetterBlock used for legibility reasons
    typedef std::vector<std::vector<LetterBlock>> Blockgrid;


private:
    sf::Text letter;
    sf::RectangleShape block;
    State state;


public:

    LetterBlock(std::string str);
    LetterBlock();

    void operator=(LetterBlock& block);

    /**
     * @brief Changes the color of the LetterBlock filler
     * @param color The sf::Color to be set
     */
    void setColor(sf::Color color) { block.setFillColor(color); }
    void setLetter(std::string letter = "") { this->letter.setString(letter); }

    void setPosition(sf::Vector2f pos);

    State getState() { return state;}

    void setState(State state) {this->state = state;}

    bool move(Blockgrid &grid, Direction direction);

    /**
     * @brief Sets the letter attribute to a capitalized letter between A-Z
     */
    void randLetter();

    void centerLetter();


    /**
     * @brief Returns a copy of the letter attribute
     */
    sf::Text getLetter() const { return letter; }

    /**
     * @brief Returns a copy of the block attribute
     */
    sf::RectangleShape getBlock() const { return block; }

    /**
     * @brief Decides whether to hide or display the LetterBlock
     * @param visible LetterBlock hidden if true
     */
    void display(bool visible);

    /**
     * @brief Checks if the LetterBlock is hidden (transparent) or not
     */
    bool isHidden();

    void initBlock();

    void initLetter(std::string str = "");

    void render(sf::RenderTarget *target);

    sf::Vector2u getPosition(const Blockgrid &grid) const;

    bool isState(State state);

};



#endif
