#ifndef GAME_WORDLE_HPP
#define GAME_WORDLE_HPP

#include<string>
#include<vector>

#include "LetterBlock.hpp"

/** This class' only prupose is to check if a valid word is contained inside the grid, be it horizontally or vertically.
 * 
 * The algorithm used to check if a word is formed will be using a hashmap
 * 
 * The class should not contain a GameGrid member, nor should it inherit the class. 
 * 
 * No method will have more than 3 layers of nesting, and each method will serve a unique function. 
 */
class Dictionary {

private:
    std::vector<std::string> dictionary;
    std::map<std::string, int> hashmap;
public:
    Dictionary();

    void initDictionnary();
    void initHashmap();
    sf::Vector2u foundHash(const std::string& word);



};

#endif