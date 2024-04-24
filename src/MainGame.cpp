
#include<iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "../headers/MainGame.hpp"
#include "../headers/Config.hpp"



MainGame::MainGame() {
    initLayout();
    initWindow();
    initComponents();
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
    //Sets window (2:1 true window scale) framerate and size
    const sf::VideoMode windowframe = sf::VideoMode(config->window_size.x,config->window_size.y);

    window = new sf::RenderWindow(windowframe,"Lettris");
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
    game = new GameGrid(input, logs, score, next);
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



bool MainGame::isRunning() {
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

    window->display(); // Displays the new frame to window
}  


void MainGame::update() {
    static uint8_t tick = 0;

    pollEvent();
    input->pollEvent(); 

    if(game->wordDestroy())
        return;

    if(!(tick % 5))
        game->blockTick();

    if(!(tick % 10)) 
        game->gridTick();
    
    if(tick == 60)
        tick = 0;

    tick++;
}


void MainGame::pollEvent() {
    sf::Event event;

    //Listens for any event on window
    while(window->pollEvent(event))
        if(event.type == sf::Event::Closed)
            window->close();
}