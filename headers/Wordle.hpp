#ifndef GAME_WORDLE_HPP
#define GAME_WORDLE_HPP

#include<string>

#include <SFML/System/Vector2.hpp>

#include "LetterBlock.hpp"

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
    sf::Vector2i findWord(const std::string& word);



};

#endif