
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
    scoreFrame = sf::RectangleShape(sf::Vector2f(213, 108));
    scoreFrame.setPosition(sf::Vector2f(693.3, 81));
    scoreFrame.setOutlineColor(sf::Color(125, 125, 125));
    scoreFrame.setOutlineThickness(3);
    scoreFrame.setFillColor(sf::Color(0, 0, 0, 0)); 
}

void GameScore::initText() {
    scoreText.setString("SCORE");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setFont(*(Config::getInstance()->font));
    scoreText.setOrigin(sf::Vector2f(scoreText.getLocalBounds().getPosition().x,scoreText.getGlobalBounds().getSize().y /2.f + scoreText.getGlobalBounds().getPosition().y));
    scoreText.setPosition(sf::Vector2f(710,153));

    topScoreText.setString("TOP");
    topScoreText.setCharacterSize(24);
    topScoreText.setFillColor(sf::Color::White);
    topScoreText.setFont(*(Config::getInstance()->font));
    topScoreText.setOrigin(sf::Vector2f(topScoreText.getLocalBounds().getPosition().x,topScoreText.getGlobalBounds().getSize().y /2.f + topScoreText.getGlobalBounds().getPosition().y));
    topScoreText.setPosition(sf::Vector2f(710,117));
}

void GameScore::render(sf::RenderTarget *target){
    target->draw(scoreFrame);
    target->draw(scoreText);
    target->draw(scoreVal);
    target->draw(topScoreText);
    target->draw(topScoreVal);
}

void GameScore::initScore() {
   

    std::ifstream scoreFile("resources/Scores.txt");
    int score, topscore = 0;

    while (scoreFile >> score)
        if(score > topscore)
            topscore = score;
    

    topScoreVal.setString(std::to_string(topscore));
    topScoreVal.setCharacterSize(24);
    topScoreVal.setFillColor(sf::Color::White);
    topScoreVal.setFont(*(Config::getInstance()->font));
    topScoreVal.setOrigin(sf::Vector2f(topScoreVal.getLocalBounds().getPosition().x + topScoreVal.getGlobalBounds().getSize().x ,topScoreVal.getGlobalBounds().getSize().y /2.f + topScoreVal.getGlobalBounds().getPosition().y));
    topScoreVal.setPosition(sf::Vector2f(890,117));






    scoreVal.setString("0");
    scoreVal.setCharacterSize(24);
    scoreVal.setFillColor(sf::Color::White);
    scoreVal.setFont(*(Config::getInstance()->font));
    scoreVal.setOrigin(sf::Vector2f(scoreVal.getLocalBounds().getPosition().x + scoreVal.getGlobalBounds().getSize().x, scoreVal.getLocalBounds().getPosition().y+ scoreVal.getGlobalBounds().getSize().y/2.0f));

    scoreVal.setPosition(sf::Vector2f(890,153));
}

void GameScore::addPoints(std::string word) {
    int points = (int)std::pow(word.size(), 3);
    int current_points = atoi(scoreVal.getString().toAnsiString().c_str()); 
    scoreVal.setString(std::to_string(current_points + points));

    scoreVal.setOrigin(sf::Vector2f(scoreVal.getLocalBounds().getPosition().x + scoreVal.getGlobalBounds().getSize().x, scoreVal.getLocalBounds().getPosition().y+ scoreVal.getGlobalBounds().getSize().y/2.0f));
}


GameScore::~GameScore() {

    //This can be slow to write the file so comment this all out in debugging
    std::ofstream scoreFile("resources/Scores.txt", std::ios::app); 

    if (scoreFile.is_open()) { 
        scoreFile << scoreVal.getString().toAnsiString() << std::endl; 
        scoreFile.close(); 
    }
}