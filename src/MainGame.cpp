

#include <SFML/Window/Event.hpp>

#include "../headers/MainGame.hpp"
#include "../headers/Config.hpp"


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

    window->draw(layout,Config::getInstance()->layoutTex); // renders layout
    game->render(window);
    logs->render(window);

    window->display(); // Displays the new fram to window
}   

void MainGame::run(){
    //main instance
    while(isRunning()){
        render();
        update();
       
    }
}


void MainGame::update() {
    pollEvent();
    game->update();
}


MainGame::MainGame() {
    initLayout();
    initWindow();
    game = new GameGrid();
    logs = new GameLogs();
}

MainGame::~MainGame() {
    delete game;
    delete window;
    delete logs;
}