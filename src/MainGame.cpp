
#include<iostream>

#include <SFML/Window/Event.hpp>

#include "../headers/MainGame.hpp"
#include "../headers/Config.hpp"


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
    display = new GameDisplay();
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

    display->render(window);
    
    window->display(); // Displays the new fram to window
}

void MainGame::run(){
    //main instance
    while(isRunning()){
        render();
        update();
       
    }
}

MainGame::MainGame(){
    initWindow();
    initInterface();
}

MainGame::~MainGame(){
    delete window;
    delete display;
}

void MainGame::update() {
    pollEvent();
    display->update();
}