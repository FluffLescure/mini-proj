#ifndef GAME_WORDLE_HPP
#define GAME_WORDLE_HPP

#include<string>

#include <SFML/System/Vector2.hpp>

#include "LetterBlock.hpp"
#include "GameLogs.hpp"


struct wordPos{
    std::string word;
    sf::Vector2i position;
};


/** This class' only prupose is to check if a valid word is contained inside the grid, be it horizontally or vertically.
 * 
 * The algorithm used to check if a word is formed will be using a hashmap
 * 
 * The class should not contain a GameGrid member, nor should it inherit the class. 
 * 
 * No method will have more than 3 layers of nesting, and each method will serve a unique function. 
 */
class Wordle {

private:
    std::map<std::string, int> hashmap;


public:
    Wordle();
    void initHashmap();
    sf::Vector2i findWordPosition(const std::string& word);
    std::string findWord_old(const std::string& word);
    std::vector<wordPos> findWord(const std::string& word);



};

#endif