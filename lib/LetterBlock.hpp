#ifndef LETTER_BLOCK_HPP
#define LETTER_BLOCK_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

/**
 * \class LetterBlock
 *
 * \brief Blocks containing letters which will be used to build the tetris program
 * inside the grid.
 *
 * \note The default set size is 100x100px as specified in constructor.
 *
 * \remark AlLows for simple display operations such as hiding the block or changing
 * it's fill color.
 * \code
 * LetterBlock block();            // defaults to a 100x100px block whith a ' '
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
private:
    char letter;
    sf::RectangleShape block;

public:
    LetterBlock(char letter = ' ', sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(100, 100))) : letter(letter), block(block){};

    /**
     * @brief Changes the color of the LetterBlock filler
     * @param color The sf::Color to be set
     */
    void setColor(sf::Color color) { block.setFillColor(color); }

    char getLetter() const { return letter; }
    sf::RectangleShape getBlock() const { return block; }

    char& fetchLetter() { return letter; }
    sf::RectangleShape& fetchBlock() { return block; }

    /**
     * @brief Decides whether to hide or display the LetterBlock
     * @param visible LetterBlock hidden if true
     */
    void display(bool visible);

    bool isHidden();
};

#endif