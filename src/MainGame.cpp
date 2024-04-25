
#include<iostream>
#include<cmath>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "../headers/MainGame.hpp"
#include "../headers/Config.hpp"



MainGame::MainGame() {
    initLayout();
    initWindow();
    initComponents();
}

constexpr void MainGame::initLayout() {
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

constexpr void MainGame::initComponents() {
    level = new GameLevel;
    input = new Input;
    logs = new GameLogs;
    score = new GameScore;
    next = new GameLetter;
    game = new GameGrid;
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



constexpr const bool MainGame::isRunning() const {
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

constexpr void MainGame::render() const {
    static sf::Texture *layoutTexture = Config::getInstance()->layoutTex;

    window->clear(); // Clear the old frame from window

    window->draw(layout, layoutTexture); // renders layout with texture

    game->render(window);
    logs->render(window);
    score->render(window);
    next->render(window);
    level->render(window);

    window->display(); // Displays the new frame to window
}  


constexpr void MainGame::update() {
    static uint8_t tick = 0;
    static uint8_t lvl = 0;
    static std::vector<WordBlock> words;

    pollEvent();
    input->pollEvent(); 

    
    words = game->wordDestroy();

    // Pauses the game while the word is being destroyed
    if(!words.empty()){
        for (WordBlock &word : words){
            logs->emplace(word.string);
            score->addPoints(word.string);
        }
        return;
    }

    if(!(tick % 5))
        game->blockMove(input->getInput());

    if(!(tick % level->getSpeed())) 
        if(!game->gridTick()) {
            game->newBlock(next->getLetter());
            next->changeLetter();
        }

    if(score->getScore() > 100 * std::pow(2, lvl)){
        lvl++;
        level->levelUp();
    }

    if(tick == 60)
        tick = 0;

    tick++;
}


constexpr void MainGame::pollEvent() {
    static sf::Event event;

    //Listens for any event on window
    while(window->pollEvent(event))
        if(event.type == sf::Event::Closed)
            window->close();
}