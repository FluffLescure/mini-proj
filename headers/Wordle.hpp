#ifndef GAME_WORDLE_HPP
#define GAME_WORDLE_HPP

#include<string>

#include <SFML/System/Vector2.hpp>


struct foundWord{
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
    // A word map that contains a unique hash for each word.
    std::map<std::string, int> map;


public:

    /**
     * @brief Constructors that call initialisation of components
    */
    Wordle();

    /**
     * @brief Initialises the map using config wordlist
    */
    void initMap();

    /**
     * @brief Finds words that are matched by the map inside a combination of characters
     * @param str the combination of characters 
     * @returns a map of the words and their position inside the combination
    */
    std::map<std::string, sf::Vector2i> findWord(std::string str);

};

#endif