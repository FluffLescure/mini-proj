

#include<iostream>

#include "../headers/Wordle.hpp"
#include "../headers/Config.hpp"

Wordle::Wordle() {
    initHashmap();
}

void Wordle::initHashmap() {
    int hash = 1; 
    //Assignes unique hash to each word from the wordlist
    for (std::string word : Config::getInstance()->wordlist) {
        hashmap[word] = hash++;
    }
}

sf::Vector2u Wordle::findWord(const std::string& word) {
    for (unsigned int i = 0; i < word.length(); i++){
        for (unsigned int j = 1; i + j <= word.length(); j++){

             std::string substring = word.substr(i, j);

            if (hashmap.find(substring) != hashmap.end() && substring.size() >1) {
                return {i,j};
            }
        }
    }
    return {0,0};
}




