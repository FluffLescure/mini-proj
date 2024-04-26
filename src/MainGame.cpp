
#include<iostream>
#include<cmath>
#include<fstream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "../headers/MainGame.hpp"
#include "../headers/Config.hpp"



MainGame::MainGame() {
    initLayout();
    initWindow();
    initComponents();
    initOver();
}

void MainGame::initLayout() {
    Config* config = Config::getInstance();
    layout_ = sf::VertexArray(sf::Quads, config->layoutPoints_.size());

    // Layout points are assimilited into a VertexArray to create a single
    // custom drawable
    for (size_t i = 0; i < config->layoutPoints_.size(); ++i) {
        layout_[i].texCoords = config->layoutPoints_[i]; // Texture layout
        layout_[i].position = config->layoutPoints_[i];
    }
}

void MainGame::initWindow() {
    Config* config = Config::getInstance();
    //Sets window framerate and size (2:1 true window scale)
    const sf::VideoMode windowframe = sf::VideoMode(config->window_size_.x,config->window_size_.y);

    window_ = new sf::RenderWindow(windowframe, config->window_title_);
    window_->setFramerateLimit(config->window_framerate_);
    window_->setVerticalSyncEnabled(true); //VSync
    window_->setVisible(true);
}

void MainGame::initComponents() {
    level_ = new GameLevel;
    input_ = new Input;
    logs_ = new GameLogs;
    score_ = new GameScore;
    next_ = new GameLetter;
    game_ = new GameGrid;
}

void MainGame::initOver(){
    over_.setFont(*Config::getInstance()->font_);
    over_.setString("Game Over\nPress 'Space' to restart");
    over_.setCharacterSize(30);
    over_.setFillColor({0, 0, 0, 0});
    over_.setOutlineColor({0, 0, 0, 0});
    over_.setOutlineThickness(1.5);
    over_.setPosition(320, 250);
}


MainGame::~MainGame() {
    delete game_;
    delete window_;
    delete input_;
    delete logs_;
    delete score_;
    delete next_;
    delete level_;
}



const bool MainGame::isRunning() {
    if(window_ == nullptr)
        return false;
    return window_->isOpen();
}



void MainGame::run(){
    //main instance
    while(isRunning()){
        render();
        update();
    }
}

void MainGame::render() {
    static sf::Texture *layoutTexture = Config::getInstance()->layoutTex_;

    window_->clear(); // Clear the old frame from window

    window_->draw(layout_, layoutTexture); // renders layout with texture

    game_->render(window_);
    logs_->render(window_);
    score_->render(window_);
    next_->render(window_);
    level_->render(window_);
    
    window_->draw(over_); // renders game over message

    window_->display(); // Displays the new frame to window
}  


void MainGame::update() {
    static uint8_t tick = 0;
    static uint8_t lvl = 0;
    static std::vector<WordBlock> words;
    static std::ofstream file = std::ofstream("resources/foundWords.txt");

    // Retreives the input from the user and polls for window events
    pollEvent();
    input_->pollEvent(); 

    // Destroys the words in the grid if they exists
    words = game_->wordDestroy();

    // Pauses the game while the word is being destroyed
    if(!words.empty()){
        for (WordBlock &word : words){
            logs_->emplace(word.string);
            score_->addPoints(word.string);

            // Writes the word to a file
            file << word.string << std::endl; 
        }
        return;
    }

    // Moves the block every 5 ticks if input is detected
    if(!(tick % 5))
        game_->blockMove(input_->getInput());

    // Moves the block down every speed ticks
    if(!(tick % level_->getSpeed()) && !game_->gridTick() ) {
        // If the grid can't move down, and no new block can be created, game over
        if(!game_->newBlock(next_->getLetter())) {
            GameOver(input_->getInput());
        }
        else
            next_->changeLetter();
    }

    // Level up values
    if(score_->getScore() > 100 * std::pow(2, lvl)){
        lvl++;
        level_->levelUp();
    }

    // Resets the tick every 60 ticks
    if(tick == 60)
        tick = 0;

    tick++;
}


void MainGame::pollEvent() {
    static sf::Event event;

    //Listens for any event on window
    while(window_->pollEvent(event))
        if(event.type == sf::Event::Closed)
            window_->close();
}



void MainGame::GameOver(const Direction &input_) {

    // Displays the game over message
    over_.setFillColor(sf::Color::Black);
    over_.setOutlineColor({255, 75, 75});


    // Restarts the game if the user presses space
    if(input_ == Direction::Space){
        delete game_;
        delete score_;
        delete next_;
        delete level_;
        delete logs_;

        initComponents();
        
        // Hides the game over message
        over_.setFillColor({0, 0, 0, 0});
        over_.setOutlineColor({0, 0, 0, 0});

        // Resets the found words file
        std::ofstream file("resources/foundWords.txt");
        file.close();
    }
}