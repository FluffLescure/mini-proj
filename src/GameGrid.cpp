
#include<iostream>

#include "../headers/GameGrid.hpp"

GameGrid::GameGrid() {
    initFrame();
    initGrid();
    initWordle();
}

void GameGrid::initGrid() {
    Config* config = Config::getInstance();

    // Creates the 2D grid and fills it with empty LetterBlocks
    grid_ = Grid(cols_, std::vector<LetterBlock>(rows_));
    for(uint8_t j=0; j < rows_; j++ ){
        for (uint8_t i=0; i < cols_; i++){
            grid_[i][j].setPosition({312+i*config->block_size_.x, 27+j*config->block_size_.y});
            grid_[i][j].display(false);
        }
    }
}


void GameGrid::initFrame() {
    gridBorder_ = sf::RectangleShape({336, 486});
    gridBorder_.setPosition({312, 27});
    gridBorder_.setOutlineColor({125,125,125});
    gridBorder_.setOutlineThickness(5);
    gridBorder_.setFillColor({0,0,0,0});
}


void GameGrid::initWordle() {
    this->wordle_ = new Wordle;
}



GameGrid::~GameGrid() {
    delete wordle_;
}



void GameGrid::render(sf::RenderTarget *target){
    target->draw(gridBorder_); // renders the frame

    // Renders each LetterBlock of the grid
    for(uint8_t j = 0; j < rows_; j++ )
        for (uint8_t i = 0; i < cols_; i++)
            grid_[i][j].render(target);   

}



const std::vector<WordBlock> GameGrid::wordDestroy() {
    static std::vector<WordBlock> stagedwords;

    // If the destroy tick is not ticking then retrieve staged words
    if(!destroyTick(false))
        stagedwords = stageWords();
    
    // If there aren't any words found then exit
    if(stagedwords.empty())
        return stagedwords;

    // Color each block staged for destruction
    for(WordBlock word : stagedwords)
        setColor(word.pos.x, word.pos.y, word.span.x, word.span.y, 0xABFFFF);
    
    // Keep ticking the destroy tick and return an empty vector until its finished 
    if(destroyTick(true))
        return std::vector<WordBlock>();
    
    // Destroy the staged words
    for(WordBlock word : stagedwords)
        blockDestroy(word.pos.x, word.pos.y, word.span.x, word.span.y);

    // Return the staged words
    return stagedwords;
}

const int GameGrid::destroyTick(const bool &keepTicking) const{
    static uint8_t destroy_tick = 0;

    // Returns the value of the destroy tick without incrementing it
    if(!keepTicking)
        return destroy_tick;
    
    // If the destroy tick is not at 30 then keep incrementing it
    if(destroy_tick != 30){
        destroy_tick++;
        return destroy_tick;
    }

    return destroy_tick = 0;
}

const std::vector<WordBlock> GameGrid::stageWords() {
    std::string crunched;
    std::vector<WordBlock> stagedwords;
    std::map<std::string, sf::Vector2u> foundWords;

    //Check for words in the columns
    for (int8_t col = cols_ - 1; col >= 0; col--) {
        // Finds words in the column after being crunched to a string
        crunched = crunchCol(col);
        foundWords = wordle_->findWord(crunched);
        for (std::pair word : foundWords)
            stagedwords.push_back({word.first, {(unsigned)col, word.second.x}, {1, word.second.y}});
    }

    //Check for words in the rows
    for (int8_t row = rows_ - 1; row >= 0; row--) {
        // Finds words in the rows after being crunched to a string
        crunched = crunchRow(row);
        foundWords = wordle_->findWord(crunched);   
        for (std::pair word : foundWords)
            stagedwords.push_back({word.first, {word.second.x, (unsigned)row}, {word.second.y, 1}});
    }

    return stagedwords;
}

const std::string GameGrid::crunchRow(const int8_t &row) {
    std::string crunched_row;
    // Iterates throught the row of LetterBlocks
    for(uint8_t i = 0; i < cols_; i++)
        // Prevents falling blocks from being computed
        if(!grid_[i][row].isState(Grounded))
            crunched_row.append(" ");
        // Appends the letter of the block to the string using the conversion operator
        else
            crunched_row.append(grid_[i][row]);
    return crunched_row;
}

const std::string GameGrid::crunchCol(const int8_t &col) {
    std::string crunched_col;

        // Iterates throught the row of LetterBlocks
    for(uint8_t j = 0; j < rows_; j++)
        // Prevents falling blocks from being computed
        if (!grid_[col][j].isState(Grounded))
            crunched_col.append(" ");
        // Appends the letter of the block to the string using the conversion operator
        else
            crunched_col.append(grid_[col][j]);
    return crunched_col;
}

void GameGrid::setColor(const uint8_t& col, const uint8_t& row, const uint8_t& colSpan, const uint8_t& rowSpan, const uint32_t& color) {
    for (uint8_t j = row; j < row + rowSpan; j++)
        for (uint8_t i = col; i < col + colSpan; i++) 
            grid_[i][j].setColor(sf::Color(color));
}

void GameGrid::blockDestroy(const uint8_t& col, const uint8_t& row, const uint8_t& colSpan, const uint8_t& rowSpan) {
    for (uint8_t j = row; j < row + rowSpan; j++) {
        for (uint8_t i = col; i < col + colSpan; i++) {
            grid_[i][j].display(false);
            grid_[i][j].setLetter(' ');
            grid_[i][j].setState(State::Fixed);
            grid_[i][j].setColor({175, 175, 175, 50});
        }
    }
}


void GameGrid::blockMove(const Direction &input) {
    // Variable used to determine if a block has already been moved.
    // This avoids moving a same block too many times within the loop
    bool moved = false;

    for (int8_t i = 0; i < cols_; i++) {
        for (int8_t j = rows_ - 1; j >= 0; j--) {
            if(grid_[i][j].isState(State::Falling) && !moved)
                moved = grid_[i][j].move(grid_, input);

            groundBlock(i,j); // grounds every block that should be grounded
        }
    }
}

void GameGrid::groundBlock(const uint8_t& i, const uint8_t& j) {
    // if the block isn't falling exit
    if(!grid_[i][j].isState(Falling))
        return; 

    // if its on the last row, or if the block beneath is grounded, then
    // set the block to grounded
    if(j == rows_ - 1 || (j < rows_ - 1 && grid_[i][j+1].isState(Grounded)))
        grid_[i][j].setState(Grounded);
}


const bool GameGrid::gridTick() {
    // This is variable used to determine if the grid has changed or not
    bool blocks_falling = false;

    // Moves the LetterBlocks that are displayed 
    for (int8_t i = 0; i < cols_; i++)
        for (int8_t j = rows_ - 1; j >= 0; j--) 
            if (!grid_[i][j].isHidden() && grid_[i][j].move(grid_, Direction::Down))
                blocks_falling = true;

    // If no blocks are falling then exit with false
    if(!blocks_falling)
        return false;

    return true;
}

const bool GameGrid::newBlock(const char &letter){
    // If a block already exists on (5,0) then exit
    if(!grid_[5][0].isHidden())
        return false;

    // Generates a random letter and color for the new block from the color scheme
    std::string color_type = "bg" + std::to_string(letter % 3);
    sf::Color color = Config::getInstance()->colorScheme_.find(color_type)->second;

    // Displays the new block on the grid
    blockDisplay({5, 0}, {1, 1}, true);
    grid_[5][0].setState(State::Falling);
    grid_[5][0].setLetter(letter);
    grid_[5][0].setColor(color);
    grid_[5][0].centerLetter();
    return true;
}

void GameGrid::blockDisplay(const sf::Vector2u& posInit, const sf::Vector2u& span, const bool& visible) {
    for (uint8_t j = posInit.y; j < posInit.y + span.y; j++)
        for (uint8_t i = posInit.x; i < posInit.x + span.x; i++) 
            grid_[i][j].display(visible);
}
