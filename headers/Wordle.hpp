#ifndef GAME_WORDLE_HPP
#define GAME_WORDLE_HPP

#include<string>
#include<map>

#include <SFML/System/Vector2.hpp>


/**
 * @class Woordle
 * @brief Provides word detection of a combination of characters
 * based on a word map created from a wordlist.
 */
class Wordle {

private:
    // A word map that contains a unique hash for each word.
    std::map<std::string, int> map_;


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
     * @returns a map of the words with their position and span inside the combination
    */
    std::map<std::string, sf::Vector2u> findWord(std::string str);

};

#endif