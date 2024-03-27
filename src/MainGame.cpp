#include "../headers/MainGame.hpp"

#include <iostream>

void MainGame::initWindow() {

    Config* config = Config::getInstance();
    //Sets window (2:1 true window scale) framerate and size
    const sf::VideoMode windowframe = sf::VideoMode(config->window_size.x,config->window_size.y);


    window = new sf::RenderWindow(windowframe,"Lettris");
    window->setFramerateLimit(config->window_framerate);
    window->setVerticalSyncEnabled(true); //VSync
    window->setVisible(true);
}

void MainGame::initInterface() {
    layout = new GameDisplay();
}

//
void MainGame::pollEvent() {
    sf::Event event;

    //Listens for any event on window 

    while(window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

bool MainGame::isRunning() {
    if(window == nullptr)
        return false;
    return window->isOpen();
}

void MainGame::render() {
    window->clear(); // Clear the old frame from window

    layout->render(window); // test functions
    
    window->display(); // Displays the new fram to window
}

void MainGame::run(){
    //main instance
    while(isRunning()){
        update();
        render();
    }
}

MainGame::MainGame(){
    initWindow();
    initInterface();
}

MainGame::~MainGame(){
    delete window;
    delete layout;
}

void MainGame::update() {
    pollEvent();
}