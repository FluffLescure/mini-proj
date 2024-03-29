#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include "LetterBlock.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <vector>

/**
 * @class GameGrid
 * @brief 2D Grid built upon LetterBlocks that shape the playing field for the game
 *
 */
class GameGrid : sf::NonCopyable {
private:
    uint8_t cols = 10;
    uint8_t rows = 15;

    sf::RectangleShape gridBorder;

    std::vector<std::vector<LetterBlock>> grid = std::vector<std::vector<LetterBlock>>(cols, std::vector<LetterBlock>(rows));

public:
    GameGrid(uint8_t cols = 10, uint8_t rows = 15);

    /**
     * @brief Updates the grid to make corresponding LetterBlocks fall 1 block lower, when possible
     */
    void gridTick();

    /**
     * @brief Destroys LetterBlocks that form a word
     * @param span Coordinates and spanning of the word staged for destruction
     */
    void blockDestroy(sf::Rect<int> span);

    /**
     * @brief Updates the visibility respective LetterBlock from grid
     * @param coord The coordinates of the block to be hidden
     */
    void blockDispay(sf::Vector2u coord, bool visible);

    /**
     * @brief Updates the visibility a zone of blocks delimited by the span entered
     * @param span The span of blocks to be hidden
     */
    void blockDisplay(sf::Vector2u posInit, sf::Vector2u span, bool visible);

    void initGrid();

    void render(sf::RenderTarget *target);

};

#endif