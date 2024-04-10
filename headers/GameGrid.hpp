#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include<stdint.h>
#include<vector>


#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


#include "LetterBlock.hpp"
#include "Input.hpp"
#include "Wordle.hpp"
#include "GameScore.hpp"

// Macro of a 2D grid of LetterBlock used for legibility reasons
typedef std::vector<std::vector<LetterBlock>> Grid;


/**
 * @class GameGrid
 * 
 * @brief 2D grid built upon LetterBlocks that shape the playing field
 * for the game. 
 * 
 * @remark This is where most of the game is controlled.
 * 
 * The dimensions of the grid are pulled from Config for scalablity. 
 * 
 * Agregation with Input and GameWordle are used to retrieve user input and 
 * determine which block - that form a valid word - must be drestroyed.
 * 
 * 'tick' will be a counter that allows control of the game grid at any chosen
 * tick.
 * 
 * 
 * 
 */
class GameGrid : sf::NonCopyable {
private:

    // dimensions of the grid;
    uint8_t cols;
    uint8_t rows;

    // Border used to draw the grid frame
    sf::RectangleShape gridBorder;

    // Agregated classes
    Input *input;
    Wordle *wordle;
    GameLogs *logs;
    GameScore *score;

    // The 2D grid where the game takes place
    Grid grid;

    // Game tick counter
    uint8_t tick = 0;

public:
    /**
     * @brief Constructor which calls the initialisation of components and
     * agregated classes
    */
    GameGrid();

    /**
     * @brief Updates the grid to make necessary LetterBlocks fall 1 block lower.
     */
    void gridTick();

    /**
     * @brief Destroys all block that form a word from the wordlist
    */
    void wordDestroy();

    /**
     * @brief Updates the falling blocks based on user input
    */
    void blockTick();

    /**
     * @brief Destroys LetterBlocks that are inside the specified span
     * @param posInit the starting position of the span
     * @param span span of blocks to be destroyed
     */
    void blockDestroy(uint8_t col, uint8_t row, uint8_t colSpan, uint8_t rowSpan);

    /**
     * @brief Updates the visibility a zone of blocks delimited by the span entered
     * @param posInit the starting position of the span
     * @param span span of blocks to be updated
     * @param visible sets the the visibility of the block
     */
    void blockDisplay(sf::Vector2u posInit, sf::Vector2u span, bool visible);


    /**
     * @brief Builds the 2D grid using dimensions pulled from Config
     * as well as the grid's bounding frame
    */
    void initGrid();

    /**
     * @brief Draws the frame for the game grid
    */
    void initFrame();

    /**
     * @brief Renders the grid's bounding frame and the 2D game grid
     * @param *target the rendered shared to other classes
    */
    void render(sf::RenderTarget *target);

    /**
     * @brief Actively retrieves user input and updates the game correspondingly.
     * Every 5 ticks the blocks are updated in relation to the input, and every
     * 30 ticks the grid is updated based on the state of the grid at that point.
    */
    void update();

    /**
     * @brief Checks if a block should be grounded based on game rules and sets
     * them grounded if needed.
     * @param i the column of the block
     * @param j the row of the block
    */
    void groundBlock(uint8_t i, uint8_t j);

    /**
     * @brief Retreives all the letters from a row and assembles them together into a string
     * @param row the row that will be crunched
     * @returns a string of all the letter in the row
    */
    std::string crunchRow(int8_t row);

    std::vector<std::vector<int>> stageWords();

    int destroyTick(bool start);

    /**
     * @brief Retreives all the letters from a column and assembles them together into a string
     * @param col the column that will be crunched
     * @returns a string of all the letter in the column
    */
    std::string crunchCol(int8_t col);

    void setColor(uint8_t col, uint8_t row, uint8_t colSpan, uint8_t rowSpan);

    void initInput();

    void initWordle();



};

#endif