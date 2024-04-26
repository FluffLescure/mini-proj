

#include<iostream>

#include "../headers/Wordle.hpp"
#include "../headers/Config.hpp"

Wordle::Wordle() {
    initMap();
}

void Wordle::initMap() {
    int hash = 1; 
    //Assignes unique hash to each word from the wordlist
    for (std::string word : Config::getInstance()->wordlist)
        map[word] = hash++;
    
}



std::map<std::string, sf::Vector2u> Wordle::findWord(std::string str){
    std::map<std::string, sf::Vector2u> foundWords;

    // A forward iteration scanning for any character combination of length bigger than 4
    // Checks if the combination corresponds to a word from the map.
    for (size_t i = 0; i < str.length(); i++){
        for (size_t length = str.length() - i; length >= 4; length--){
            std::string substring = str.substr(i, length);

            if (map.find(substring) != map.end()) 
                foundWords.emplace(std::pair(substring, sf::Vector2u(i, length)));
        }
    }

    // Reverses the string before iterating backwards
    std::reverse(str.begin(), str.end());

    for (ssize_t i = str.length(); i >= 0; i--){
        for (size_t length = 4; length < str.length() - i; length++){
            std::string substring = str.substr(i, length);

            if (map.find(substring) != map.end()) 
                foundWords.emplace(std::pair(substring, sf::Vector2u((int)str.size() - i - length, length)));
        }
    }
    return foundWords;
}



