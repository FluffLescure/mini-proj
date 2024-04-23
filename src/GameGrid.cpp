
#include<iostream>

#include "../headers/GameGrid.hpp"


GameGrid::GameGrid() {
    initFrame();
    initGrid();
    initInput();
    initComponents();
}

void GameGrid::initFrame() {
    // Draws the bounding frame of the grid
    gridBorder = sf::RectangleShape({336, 486});
    gridBorder.setPosition({312, 27});
    gridBorder.setOutlineColor({125,125,125});
    gridBorder.setOutlineThickness(5);
    gridBorder.setFillColor({0,0,0,0});
}

void GameGrid::initGrid() {
    Config* config = Config::getInstance();

    // Creates the 2D grid and fills it with empty LetterBlocks
    grid = Grid(cols, std::vector<LetterBlock>(rows));
    for(uint8_t j=0; j < rows; j++ ){
        for (uint8_t i=0; i < cols; i++){
            grid[i][j].setPosition({312+i*config->block_size.x, 27+j*config->block_size.y});
            grid[i][j].display(false);
        }
    }
}

 void GameGrid::initInput(){
    input = new Input;
 }

void GameGrid::initComponents() {
    wordle = new Wordle;
    logs = new GameLogs;
    score = new GameScore;
    next = new GameLetter;
}



GameGrid::~GameGrid() {
    delete input;
    delete wordle;
    delete logs;
    delete score;
    delete next;
}



void GameGrid::render(sf::RenderTarget *target){
    target->draw(gridBorder); // renders the frame

    // Renders each LetterBlock of the grid
    for(uint8_t j = 0; j < rows; j++ )
        for (uint8_t i = 0; i < cols; i++)
            grid[i][j].render(target);   

    logs->render(target);
    score->render(target);
    next->render(target);

}



void GameGrid::update() {
    static uint8_t tick = 0;

    // Retrieves user input
    input->pollEvent();

    if(wordDestroy())
        return;

    if(!(tick % 5))
        blockTick();

    if(!(tick % 30)) 
        gridTick();
    
    if(tick == 60)
        tick = 0;

    tick++;
}


bool GameGrid::wordDestroy(){
    static std::vector<std::vector<int>> stagedwords;

    // if the destroy tick is inactive then retrieve staged words
    if(!destroyTick(false))
        stagedwords = stageWords();
    
    // if there are words found then pause the grid, else exit
    if(stagedwords.empty())
        return false;

    for(std::vector<int> word : stagedwords){
        if(word[2] == -1)
            setColor(word[0], word[1], word[3], 1);
        else 
            setColor(word[1], word[0], 1, word[2]);
    }
    
    if(destroyTick(true))
        return true;

    for(std::vector<int> word : stagedwords){
        if(word[2] == -1)
            blockDestroy(word[0], word[1], word[3], 1);
        else 
            blockDestroy(word[1], word[0], 1, word[2]);
    }

    return false;
}

int GameGrid::destroyTick(bool keepTicking){
    static uint8_t destroy_tick = 0;

    if(!keepTicking)
        return destroy_tick;
    
    if(destroy_tick != 30){
        destroy_tick++;
        return destroy_tick;     
    }

    destroy_tick = 0;
    return 0;
}

std::vector<std::vector<int>> GameGrid::stageWords() {
    std::string crunched;
    std::vector<std::vector<int>> stagedwords;
    std::map<std::string, sf::Vector2i> foundWords;

    for (int8_t col = cols - 1; col >= 0; col--) {
        crunched = crunchCol(col);
        foundWords = wordle->findWord(crunched);
        for (std::pair word : foundWords){
            stagedwords.push_back({word.second.x, col, word.second.y, -1});
            logs->emplace(word.first);
            score->addPoints(word.first);
        }
    }

    for (int8_t row = rows - 1; row >= 0; row--) {
        crunched = crunchRow(row);
        foundWords = wordle->findWord(crunched);
        for (std::pair word : foundWords) {
            stagedwords.push_back({word.second.x, row, -1, word.second.y});
            logs->emplace(word.first);
            score->addPoints(word.first);
        }
    }

    return stagedwords;
}

std::string GameGrid::crunchRow(int8_t row) {
    std::string crunched_row;
    for(uint8_t i = 0; i < cols; i++)
        if(!grid[i][row].isState(Grounded))
            crunched_row.append(" ");
        else
            crunched_row.append(grid[i][row]);
    return crunched_row;
}

std::string GameGrid::crunchCol(int8_t col) {
    std::string crunched_col;
    for(uint8_t j = 0; j < rows; j++)
        if (!grid[col][j].isState(Grounded))
            crunched_col.append(" ");
        else
            crunched_col.append(grid[col][j]);
    return crunched_col;
}

void GameGrid::setColor(uint8_t col, uint8_t row, uint8_t colSpan, uint8_t rowSpan){
    for (uint8_t j = row; j < row + rowSpan; j++)
        for (uint8_t i = col; i < col + colSpan; i++) 
            grid[i][j].setColor({122, 220, 220});
}

void GameGrid::blockDestroy(uint8_t col, uint8_t row, uint8_t colSpan, uint8_t rowSpan) {
    for (uint8_t j = row; j < row + rowSpan; j++) {
        for (uint8_t i = col; i < col + colSpan; i++) {
            grid[i][j].display(false);
            grid[i][j].setLetter(' ');
            grid[i][j].setState(State::Fixed);
            grid[i][j].setColor({175, 175, 175, 50});
        }
    }
}


void GameGrid::blockTick() {
    // Variable used to determine if a block has already been moved.
    // This avoids moving a same block too many times within the loop
    bool moved = false;

    for (int8_t i = 0; i < cols; i++) {
        for (int8_t j = rows - 1; j >= 0; j--) {
            if(grid[i][j].isState(State::Falling) && !moved)
                moved = grid[i][j].move(grid, input->getDirection());

            groundBlock(i,j); // grounds every block that should be grounded
        }
    }
}

void GameGrid::groundBlock(uint8_t i, uint8_t j) {
    // if the block isn't falling exit
    if(!grid[i][j].isState(Falling))
        return; 

    // if its on the last row or if the block beneath is grounded, then
    // set the block to grounded
    if(j == rows - 1 || (j < rows - 1 && grid[i][j+1].isState(Grounded)))
        grid[i][j].setState(Grounded);
}


void GameGrid::gridTick() {
    // This is variable used to determine if the grid has changed or not
    bool blocks_falling = false;

    // Moves the LetterBlocks that are displayed 
    for (int8_t i = 0; i < cols; i++)
        for (int8_t j = rows - 1; j >= 0; j--) 
            if (!grid[i][j].isHidden() && grid[i][j].move(grid, Direction::Down))
                blocks_falling = true;

    // if no blocks are falling then add a new falling LetterBlock
    if(!blocks_falling && grid[5][0].isHidden()) {
        blockDisplay({5, 0}, {1, 1}, true);
        grid[5][0].setState(State::Falling);
        grid[5][0].setLetter(next->getLetter());
        grid[5][0].centerLetter();
        next->changeLetter();
    }
}

void GameGrid::blockDisplay(sf::Vector2u posInit, sf::Vector2u span, bool visible) {
    for (uint8_t j = posInit.y; j < posInit.y + span.y; j++)
        for (uint8_t i = posInit.x; i < posInit.x + span.x; i++) 
            grid[i][j].display(visible);
}
























