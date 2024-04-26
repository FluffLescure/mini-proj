
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
    layout = sf::VertexArray(sf::Quads, config->layoutPoints.size());

    // Layout points are assimilited into a VertexArray to create a single
    // custom drawable
    for (size_t i = 0; i < config->layoutPoints.size(); ++i) {
        layout[i].texCoords = config->layoutPoints[i]; // Texture layout
        layout[i].position = config->layoutPoints[i];
    }
}

void MainGame::initWindow() {
    Config* config = Config::getInstance();
    //Sets window framerate and size (2:1 true window scale)
    const sf::VideoMode windowframe = sf::VideoMode(config->window_size.x,config->window_size.y);

    window = new sf::RenderWindow(windowframe, config->window_title);
    window->setFramerateLimit(config->window_framerate);
    window->setVerticalSyncEnabled(true); //VSync
    window->setVisible(true);
}

void MainGame::initComponents() {
    level = new GameLevel;
    input = new Input;
    logs = new GameLogs;
    score = new GameScore;
    next = new GameLetter;
    game = new GameGrid;
}

void MainGame::initOver(){
    over.setFont(*Config::getInstance()->font);
    over.setString("Game Over\nPress 'Space' to restart");
    over.setCharacterSize(30);
    over.setFillColor({0, 0, 0, 0});
    over.setOutlineColor({0, 0, 0, 0});
    over.setOutlineThickness(1.5);
    over.setPosition(320, 250);
}


MainGame::~MainGame() {
    delete game;
    delete window;
    delete input;
    delete logs;
    delete score;
    delete next;
    delete level;
}



const bool MainGame::isRunning() {
    if(window == nullptr)
        return false;
    return window->isOpen();
}



void MainGame::run(){
    //main instance
    while(isRunning()){
        render();
        update();
    }
}

void MainGame::render() {
    static sf::Texture *layoutTexture = Config::getInstance()->layoutTex;

    window->clear(); // Clear the old frame from window

    window->draw(layout, layoutTexture); // renders layout with texture

    game->render(window);
    logs->render(window);
    score->render(window);
    next->render(window);
    level->render(window);
    
    window->draw(over); // renders game over message

    window->display(); // Displays the new frame to window
}  


void MainGame::update() {
    static uint8_t tick = 0;
    static uint8_t lvl = 0;
    static std::vector<WordBlock> words;
    static std::ofstream file = std::ofstream("resources/foundWords.txt");

    // Retreives the input from the user and polls for window events
    pollEvent();
    input->pollEvent(); 

    // Destroys the words in the grid if they exists
    words = game->wordDestroy();

    // Pauses the game while the word is being destroyed
    if(!words.empty()){
        for (WordBlock &word : words){
            logs->emplace(word.string);
            score->addPoints(word.string);

            // Writes the word to a file
            file << word.string << std::endl; 
        }
        return;
    }

    // Moves the block every 5 ticks if input is detected
    if(!(tick % 5))
        game->blockMove(input->getInput());

    // Moves the block down every speed ticks
    if(!(tick % level->getSpeed()) && !game->gridTick() ) {
        // If the grid can't move down, and no new block can be created, game over
        if(!game->newBlock(next->getLetter())) {
            GameOver(input->getInput());
        }
        else
            next->changeLetter();
    }

    // Level up values
    if(score->getScore() > 100 * std::pow(2, lvl)){
        lvl++;
        level->levelUp();
    }

    // Resets the tick every 60 ticks
    if(tick == 60)
        tick = 0;

    tick++;
}


void MainGame::pollEvent() {
    static sf::Event event;

    //Listens for any event on window
    while(window->pollEvent(event))
        if(event.type == sf::Event::Closed)
            window->close();
}



void MainGame::GameOver(const Direction &input) {

    // Displays the game over message
    over.setFillColor(sf::Color::Black);
    over.setOutlineColor({255, 75, 75});


    // Restarts the game if the user presses space
    if(input == Direction::Space){
        delete game;
        delete score;
        delete next;
        delete level;
        delete logs;

        initComponents();
        
        // Hides the game over message
        over.setFillColor({0, 0, 0, 0});
        over.setOutlineColor({0, 0, 0, 0});
    }
}