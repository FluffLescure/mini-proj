#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include "LetterBlock.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <vector>

/**
 * @class GameGrid
 * @brief 2D Grid built upon LetterBlocks that shape the playing field for the game
 */
class GameGrid : sf::NonCopyable {
private:
    u_int8_t rows = 15;
    u_int8_t cols = 10;

    std::vector<std::vector<LetterBlock>> grid = std::vector<std::vector<LetterBlock>>(rows, std::vector<LetterBlock>(cols));

public:
    GameGrid();
    GameGrid(u_int8_t rows, u_int8_t cols);

    /**
     * @brief Updates the grid to make corresponding LetterBlocks fall 1 block lower, when possible
     */
    void gridTick(void);

    /**
     * @brief Destroys LetterBlocks that form a word
     * @param span Coordinates and spanning of the word staged to delete
     */
    void gridDestroy(sf::Rect<int> span);

    /**
     * @brief Updates the visibility respective LetterBlock from grid
     * @param block The block to be hidden
     */
    void gridDispay(LetterBlock block, bool hide);

    /**
     * @brief Updates the visibility a zone of blocks delimited by the span entered
     * @param span The span of blocks to be hidden
     */
    void gridDisplay(sf::Rect<int> span, bool hide);
};

#endif