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
#include "GameLogs.hpp"
#include "GameScore.hpp"
#include "GameLetter.hpp"
#include "LetterBlock.hpp"
#include "Wordle.hpp"


// Macro of a 2D grid of LetterBlock used to improve legibility
using Grid = std::vector<std::vector<LetterBlock>>;


struct WordBlock {
    std::string word;
    sf::Vector2u pos = {0, 0};
    sf::Vector2u span = {0, 0};
};


/**
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
class GameGrid : sf::NonCopyable {
private:

    // dimensions of the grid;
    static constexpr uint8_t cols = Config::gamegrid_cols;
    static constexpr uint8_t rows = Config::gamegrid_rows;

    // Border used to draw the grid frame
    sf::RectangleShape gridBorder;

    // Agregated classes
    Input *input;
    Wordle *wordle;
    GameLogs *logs;
    GameScore *score;
    GameLetter *next;

    // The 2D grid where the game takes place
    Grid grid;

public:

    /**
     * @brief Constructor which calls the initialisation of components and
     *  agregated classes
    */
    GameGrid(Input *input = nullptr, GameLogs *logs = nullptr, GameScore *score = nullptr, GameLetter *next = nullptr);

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
    void initComponents(Input *input = nullptr, GameLogs *logs = nullptr, GameScore *score = nullptr, GameLetter *next = nullptr);


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
    */
    const bool wordDestroy();

    /**
     * @brief A tick counter which is used to time the destruction
     * of staged words.
     * @remark Allows the possibility to read the counter value without
     *  incrementing the counter.
     * @param keepTicking keeps ticking the counter or not
     * @return The value of the destroy counter
    */
    constexpr int destroyTick(const bool &keepTicking) const;

    /**
     * @brief Retrieves a list of staged words identified from the grid which
     *  includes their position([0] and [1]) and span([2] and [3]).
     * @return Staged words that need to be destroyed
    */
    std::vector<WordBlock> stageWords();

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
     * @param col the column of the first letter of the block
     * @param row the row of the first letter of the block
     * @param colSpan span of blocks in the column 
     * @param rowSpan span of blocks in the row
    */
    void setColor(uint8_t col, uint8_t row, uint8_t colSpan, uint8_t rowSpan);

    /**
     * @brief Destroys LetterBlocks that are inside the specified span
     * @param col the column of the first letter of the block
     * @param row the row of the first letter of the block
     * @param colSpan span of blocks in the column 
     * @param rowSpan span of blocks in the row
     */
    void blockDestroy(uint8_t col, uint8_t row, uint8_t colSpan, uint8_t rowSpan);


    /**
     * @brief Updates the falling blocks based on user input and grounds them
     *  when needed.
    */
    void blockTick();

    /**
     * @brief Checks if a block should be grounded based on game rules and sets
     *  them grounded if needed.
     * @param i the column of the block
     * @param j the row of the block
    */
    void groundBlock(uint8_t i, uint8_t j);


    /**
     * @brief Updates the grid to make necessary LetterBlocks fall 1 block down and 
     *  adds a new block when no blocks can fall.
     */
    void gridTick();

    void newBlock();

    /**
     * @brief Updates the visibility a zone of blocks delimited by the span entered
     * @param posInit the starting position of the span
     * @param span span of blocks to be updated
     * @param visible sets the the visibility of the block
     */
    void blockDisplay(sf::Vector2u posInit, sf::Vector2u span, bool visible);

    
   

    

    

    

   

    

   

   




};

#endif