#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include "LetterBlock.hpp"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Rect.hpp>
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
     * @brief Destroys LetterBlocks that form a word horizontally
     * @param row_start Row starting possition to delete
     * @param row_end Row ending position to delete
     */
    void gridDestroyH(sf::Rect  );

    /**
     * @brief Destroys LetterBlocks that form a word horizontally
     * @param col_start Row starting possition to delete
     * @param col_end Row ending position to delete
     */
    void gridDestroyV(sf::Vector2u col_span);
};

#endif