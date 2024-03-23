#include "../headers/MainGame.hpp"

#include <iostream>

void MainGame::initWindow() {

    //Sets window (2:1 true window scale) framerate and size
    const uint8_t framerate = 60; 
    const sf::VideoMode windowframe = sf::VideoMode(960,540);

    window = new sf::RenderWindow(windowframe,"Lettris");
    window->setFramerateLimit(framerate);
    window->setVerticalSyncEnabled(true); //VSync
    window->setVisible(true);
}

void MainGame::initFont() {

    //initialises fonts for text implementation (untested)
    font = new sf::Font();
    const char* fontfile = "ressources/Lato-Black.ttf"; 

    if (font->loadFromFile(fontfile) == false) {
        std::cout << "ERROR: Failed to load " << fontfile << std::endl;
        abort();
    }
}

void MainGame::initInterface() {
    layout = new GameDisplay();
}

//
void MainGame::pollEvent() {
    sf::Event event;

    //Listens for any event on window (unused yet)

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
        render();
    }
}

MainGame::MainGame(){
    initWindow();
    initInterface();
}