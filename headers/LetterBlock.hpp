#ifndef LETTER_BLOCK_HPP
#define LETTER_BLOCK_HPP


#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
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
    sf::Text letter;
    sf::RectangleShape block;
    sf::Font font;

public:
    LetterBlock(std::string str);
    LetterBlock();

    void operator=(LetterBlock& block);

    /**
     * @brief Changes the color of the LetterBlock filler
     * @param color The sf::Color to be set
     */
    void setColor(sf::Color color) { block.setFillColor(color); }
    void setLetter(sf::Text letter) { this->letter = letter; }
    void setLetter(std::string letter = "") { this->letter.setString(letter); }

    void setPosition(sf::Vector2f pos);


    /**
     * @brief Returns a copy of the letter attribute
     */
    sf::Text getLetter() const { return letter; }

    /**
     * @brief Returns a copy of the block attribute
     */
    sf::RectangleShape getBlock() const { return block; }

    /**
     * @brief Returns a reference to the letter attribute
     * @warning Allows for direct modification to the attribute outside class scope
     */
    sf::Text& fetchLetter() { return letter; }

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

    void initLetter(std::string str = " ");

    void render(sf::RenderTarget *target);

};

#endif
