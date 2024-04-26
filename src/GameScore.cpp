
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
    scoreFrame_ = sf::RectangleShape({213, 108});
    scoreFrame_.setPosition({693.3, 81});
    scoreFrame_.setOutlineColor({125, 125, 125});
    scoreFrame_.setOutlineThickness(3);
    scoreFrame_.setFillColor({0, 0, 0, 0}); 
}


void GameScore::initText() {
    scoreText_.setString("SCORE");
    scoreText_.setCharacterSize(24);
    scoreText_.setFillColor(sf::Color::White);
    scoreText_.setFont(*Config::getInstance()->font_);
    scoreText_.setOrigin({0, scoreText_.getGlobalBounds().height / 2.f}); // right center alignment
    scoreText_.setPosition({710, 153});

    topScoreText_.setString("TOP");
    topScoreText_.setCharacterSize(24);
    topScoreText_.setFillColor(sf::Color::White);
    topScoreText_.setFont(*Config::getInstance()->font_);
    topScoreText_.setOrigin({0, topScoreText_.getGlobalBounds().height /2.f}); // right center alignment
    topScoreText_.setPosition({710, 114});
}


void GameScore::initScore() {
    std::ifstream scoreFile(Config::scores_file_);
    unsigned int score, topscore = 0;

    // Retrieves the biggest logged score
    while (scoreFile >> score)
        if(score > topscore)
            topscore = score;

    topScoreVal_.setString(std::to_string(topscore));
    topScoreVal_.setCharacterSize(24);
    topScoreVal_.setFillColor(sf::Color::White);
    topScoreVal_.setFont(*Config::getInstance()->font_);
    topScoreVal_.setOrigin({topScoreVal_.getGlobalBounds().width ,topScoreVal_.getGlobalBounds().height / 2.f}); // left center alignment
    topScoreVal_.setPosition({890, 114});

    scoreVal_.setString("0");
    scoreVal_.setCharacterSize(24);
    scoreVal_.setFillColor(sf::Color::White);
    scoreVal_.setFont(*Config::getInstance()->font_);
    scoreVal_.setOrigin({scoreVal_.getGlobalBounds().width, scoreVal_.getGlobalBounds().height / 2.0f}); // left center alignment
    scoreVal_.setPosition({890, 153});
}



GameScore::~GameScore() {
    //In debugging the writting can be slow
    std::ofstream scoreFile(Config::scores_file_, std::ios::app); 

    //Write scores to file
    if (scoreFile.is_open()) { 
        scoreFile << scoreVal_.getString().toAnsiString() << std::endl; 
        scoreFile.close(); 
    }
}


const int GameScore::getScore() const {
    return atoi(scoreVal_.getString().toAnsiString().c_str());
}


void GameScore::addPoints(const std::string& word) {
    // Calculates the points based on the word size
    int points = (int)std::pow(word.size(), 3);
    int current_points = getScore(); 

    scoreVal_.setString(std::to_string(current_points + points));
    scoreVal_.setOrigin({scoreVal_.getGlobalBounds().width, scoreVal_.getGlobalBounds().height / 2.0f}); // left center alignment
}



void GameScore::render(sf::RenderTarget *target) const {
    target->draw(scoreFrame_);
    target->draw(scoreText_);
    target->draw(scoreVal_);
    target->draw(topScoreText_);
    target->draw(topScoreVal_);
}