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
 * LetterBlock block();            // defaults to a 33.6x32.4px block whith a ' '
 *                                    character
 * block.display(false);           // hides the block (alpha = 0)
 * \endcode
 *
 * Utilities such as get and set are provided to respectfully retrieve data or modify
 * the object attribute.
 * \code
 * LetterBlock block('A');                      // Creates a 33.6x32.4px block containing
 *                                                 the letter 'A'
 * 
 * char letter = block.getLetter();             // Copies the 'letter' attribute
 * block.setLetter('B');                        // Sets the letter to 'B'
 * block.setPosition({0,0});                    // Changes the position of the LetterBlock
 * block.setState(State::Falling);              // Changes the block state
 * if (block.isState(State::Falling)) {         // Probes the state of the block
 *      block.setColor(sf::Color::Red)          // Changes the fill color of the block
 * }
 * if (block.isHidden()) {                      // Checks if block is hidden
 *      block.getPosition(grid);                // Returns the position of the block
 *                                                 inside a LetterBlock 2D grid
 * }
 * State state = block.getState();              // Retrieves the block state
 * sf::RectangleShape rect = block.getBlock();  // Retrieves a copy of the block attribute
 * \endcode
 * 
 * For its use in a 2D grid an overload of the = operator was made to be able to move 
 * the LetterBlock porperties to another without changing the position of any of them.
 * \code
 * LetterBlock block1('A');
 * Letterblock block2('B');
 * block1.setColor(sf::Color::Black);
 * block2.setColor(sf::Color::Red);
 * block1 = block2                      // block2's properties are transfered to block1 
 * \endcode
 */
class LetterBlock {

    // Macro of a 2D grid of LetterBlock used for legibility reasons
    typedef std::vector<std::vector<LetterBlock>> Blockgrid;


private:
    sf::Text letter;
    sf::RectangleShape block;
    State state;


public:
    /**
     * @brief Default class constructor that can accept a letter to display
    */
    LetterBlock(std::string str = "");

    /**
     * @brief Operator used for the sole purpose of transfering the LetterBlock
     * porperties to another block without changing anyone's position.
     * @remark This will be used inside the 2D grid to create the illusion of moving
     * blocks by transfering letter and fill color to the next.
     * @param &block the block that will be transfered.
    */
    void operator=(LetterBlock& block);

    /**
     * @brief Initialises the block with a set of given properties
    */
    void initBlock();
    /**
     * @brief Initialises the letter with a set of given properties
    */
    void initLetter(std::string str = "");

    /**
     * @brief Changes the color of the LetterBlock filler
     * @param color The color to be set
     */
    void setColor(sf::Color color) { block.setFillColor(color); }
    /**
     * @brief Changes the letter of the LetterBlock 
     * @param letter the letter to be set
     */
    void setLetter(std::string letter = "") { this->letter.setString(letter); }
    /**
     * @brief Changes the state of the LetterBlock 
     * @param state the state to be set
     */
    void setState(State state) {this->state = state;}
    /**
     * @brief Changes the position of the LetterBlock 
     * @param pos the position to be set
     */
    void setPosition(sf::Vector2f pos);

    /**
     * @brief Return the current state of the LetterBlock
    */
    State getState() const { return state; }

    /**
     * @brief Returns a copy of the block attribute
     */
    sf::RectangleShape getBlock() const { return block; }

    /**
     * @brief Returns a copy of the letter attribute
     */
    sf::Text getLetter() const { return letter; }

    /**
     * @brief Return the current position of the LetterBlock inside the 2D LetterBlock
     * grid
    */
    sf::Vector2u getPosition(const Blockgrid &grid) const;

    /**
     * @brief Tests if the state of the block is the same as the parameter 
     * @param state the state to be tested for
     * @returns result of the test, either true or false
    */
    bool isState(State state);

    /**
     * @brief Checks if the LetterBlock is hidden (transparent) or not
     * @returns result of the check, either true or false
     */
    bool isHidden();

    /**
     * @brief Moves the LetterBlock inside the 2D grid according to the given direction
     * @param &grid the 2D grid of LetterBlock where its contained
     * @param direction the direction of movement of the block
     * @returns true if the block was succesfully moved
    */
    bool move(Blockgrid &grid, Direction direction);

    /**
     * @brief Sets the letter attribute to a capitalized letter between A-Z
     */
    void randLetter();

    /**
     * @brief Centers the letter to the center of the LetterBlock. 
     * @remark Since this is based on the size and shape of the letter, it should
     * be called everytime the letter is changed to guranteee its correct positioning 
    */
    void centerLetter();

    /**
     * @brief Decides whether to hide or display the LetterBlock
     * @param visible LetterBlock hidden if true
     */
    void display(bool visible);

    /**
     * @brief Renders the components of the LetterBlock
     * @param *target the rendered shared amongst classes
    */
    void render(sf::RenderTarget *target);

};



#endif
