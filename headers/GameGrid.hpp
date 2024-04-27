#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include<stdint.h>
#include<vector>


#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Config.hpp"
#include "Input.hpp"
#include "LetterBlock.hpp"
#include "Wordle.hpp"


// Macro of a 2D grid of LetterBlock used to improve legibility
using Grid = std::vector<std::vector<LetterBlock>>;


struct WordBlock {
    std::string string;
    sf::Vector2u pos = {0, 0};
    sf::Vector2u span = {0, 0};
};


/**
 * @author Tom Paillet
 * @class GameGrid
 * 
 * @brief 2D grid built upon LetterBlocks that shape the playing field
 *  for the game. 
 * 
 * @remark This is where most of the game is controlled by processing game data
 *  with its related classes
 * 
 * The dimensions of the grid are pulled from Config. 
 * 
 * Agregation with Input and GameWordle are used to retrieve user input and 
 * determine which block - that form a valid word - must be drestroyed. Other
 * aggregation are used as related components that communicate with the GameGrid
 * to output the correct game values.
 * 
 */
class GameGrid {
private:

    // dimensions of the grid;
    static constexpr const uint8_t cols_ = Config::gamegrid_cols_;
    static constexpr const uint8_t rows_ = Config::gamegrid_rows_;

    // Border used to draw the grid frame
    sf::RectangleShape gridBorder_;

    // Agregated classes
    Wordle *wordle_;
    
    // The 2D grid where the game takes place
    Grid grid_;

public:

    /**
     * @brief Constructor which calls the initialisation of components and
     *  agregated classes
    */
    GameGrid();

    /**
     * @brief Builds the 2D grid using dimensions pulled from Config
     *  as well as the grid's bounding frame
    */
    void initGrid();

    /**
     * @brief Draws the frame for the game grid
    */
    void initFrame();

    /**
     * @brief Initialises links with other required classes when required
    */
    void initWordle();


    /**
     * @brief Frees the wordle link
     * @remark The wordle link is the only one which freed as the other
     * links are destroyed in MainGame
    */
    ~GameGrid();


    /**
     * @brief Renders the grid's bounding frame and the 2D game grid
     * @param *target the rendered shared by other classes
    */
    void render(sf::RenderTarget *target);


    /**
     * @brief Destroys all block that form a word from the wordlist
     * @returns a vecotr of WordBlock that were destroyed
    */
    const std::vector<WordBlock> wordDestroy();

    /**
     * @brief A tick counter which is used to time the destruction
     * of staged words.
     * @remark Allows the possibility to read the counter value without
     *  incrementing the counter.
     * @param keepTicking keeps ticking the counter or not
     * @return The value of the destroy counter
    */
    const int destroyTick(const bool &keepTicking = true) const;

    /**
     * @brief Retrieves a list of staged words identified from the grid which
     *  includes their position([0] and [1]) and span([2] and [3]).
     * @return Staged words that need to be destroyed
    */
    const std::vector<WordBlock> stageWords();

    /**
     * @brief Retreives all the letters from a row and crunches them together
     *  in a string.
     * @param row the row that will be crunched
     * @returns a string of all the letters in the row
    */
    const std::string crunchRow(const int8_t &row);

    /**
     * @brief Retreives all the letters from a column and crunches them together
     *  in a string.
     * @param col the column that will be crunched
     * @returns a string of all the letters in the column
    */
    const std::string crunchCol(const int8_t &col);

    /**
     * @brief Changes the color of the span of blocks given as parameter.
     * @param pos the position of the first letter of the block
     * @param span the span of the blocks
    */
    void setColor(const sf::Vector2u &pos, const sf::Vector2u &span, const uint32_t& color);

    /**
     * @brief Destroys LetterBlocks that are inside the specified span
     * @param pos the position of the first letter of the block
     * @param span the span of the blocks
     */
    void blockDestroy(const sf::Vector2u &pos, const sf::Vector2u &span);


    /**
     * @brief Updates the falling blocks based on user input and grounds them
     *  when needed.
     * @param input the direction of the block
    */
    void blockMove(const Direction &input);

    /**
     * @brief Checks if a block should be grounded based on game rules and grounds
     *  them if needed.
     * @param i the column of the block
     * @param j the row of the block
    */
    void groundBlock(const uint8_t& i, const uint8_t& j);


    /**
     * @brief Updates the grid to make necessary LetterBlocks fall 1 block down and 
     *  adds a new block when no blocks can fall.
     * @returns true if a block moved down, false otherwise
     */
    const bool gridTick();

    /**
     * @brief Adds a new block to the grid
     * @param letter the letter of the new block
     * @returns true if a block was added, false otherwise
    */
    const bool newBlock(const char &letter = ' ');

    /**
     * @brief Updates the visibility a zone of blocks delimited by the span entered
     * @param posInit the starting position of the span
     * @param span span of blocks to be updated
     * @param visible sets the the visibility of the block
     */
    void blockDisplay(const sf::Vector2u& posInit, const sf::Vector2u& span, const bool& visible);

};

#endif