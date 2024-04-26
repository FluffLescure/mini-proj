
#include<cmath>
#include<fstream>
#include<iostream>

#include <SFML/System/Vector2.hpp>

#include "../headers/GameScore.hpp"
#include "../headers/Config.hpp"

GameScore::GameScore() {
    initFrame();
    initScore();
    initText();
}

void GameScore::initFrame() {
    scoreFrame = sf::RectangleShape({213, 108});
    scoreFrame.setPosition({693.3, 81});
    scoreFrame.setOutlineColor({125, 125, 125});
    scoreFrame.setOutlineThickness(3);
    scoreFrame.setFillColor({0, 0, 0, 0}); 
}


void GameScore::initText() {
    scoreText.setString("SCORE");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setFont(*Config::getInstance()->font);
    scoreText.setOrigin({0, scoreText.getGlobalBounds().height / 2.f}); // right center alignment
    scoreText.setPosition({710, 153});

    topScoreText.setString("TOP");
    topScoreText.setCharacterSize(24);
    topScoreText.setFillColor(sf::Color::White);
    topScoreText.setFont(*Config::getInstance()->font);
    topScoreText.setOrigin({0, topScoreText.getGlobalBounds().height /2.f}); // right center alignment
    topScoreText.setPosition({710, 114});
}


void GameScore::initScore() {
    std::ifstream scoreFile(Config::scores_file);
    unsigned int score, topscore = 0;

    // Retrieves the biggest logged score
    while (scoreFile >> score)
        if(score > topscore)
            topscore = score;

    topScoreVal.setString(std::to_string(topscore));
    topScoreVal.setCharacterSize(24);
    topScoreVal.setFillColor(sf::Color::White);
    topScoreVal.setFont(*Config::getInstance()->font);
    topScoreVal.setOrigin({topScoreVal.getGlobalBounds().width ,topScoreVal.getGlobalBounds().height / 2.f}); // left center alignment
    topScoreVal.setPosition({890, 114});

    scoreVal.setString("0");
    scoreVal.setCharacterSize(24);
    scoreVal.setFillColor(sf::Color::White);
    scoreVal.setFont(*Config::getInstance()->font);
    scoreVal.setOrigin({scoreVal.getGlobalBounds().width, scoreVal.getGlobalBounds().height / 2.0f}); // left center alignment
    scoreVal.setPosition({890, 153});
}



GameScore::~GameScore() {
    //In debugging the writting can be slow
    std::ofstream scoreFile(Config::scores_file, std::ios::app); 

    //Write scores to file
    if (scoreFile.is_open()) { 
        scoreFile << scoreVal.getString().toAnsiString() << std::endl; 
        scoreFile.close(); 
    }
}


const int GameScore::getScore() const {
    return atoi(scoreVal.getString().toAnsiString().c_str());
}


void GameScore::addPoints(const std::string& word) {
    // Calculates the points based on the word size
    int points = (int)std::pow(word.size(), 3);
    int current_points = getScore(); 

    scoreVal.setString(std::to_string(current_points + points));
    scoreVal.setOrigin({scoreVal.getGlobalBounds().width, scoreVal.getGlobalBounds().height / 2.0f}); // left center alignment
}



void GameScore::render(sf::RenderTarget *target) const {
    target->draw(scoreFrame);
    target->draw(scoreText);
    target->draw(scoreVal);
    target->draw(topScoreText);
    target->draw(topScoreVal);
}