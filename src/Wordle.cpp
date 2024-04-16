

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

sf::Vector2i Wordle::findWordPosition(const std::string& word) {
    for (int i = 0; i < (int)word.length(); i++){
        for (int j = word.length()-i; j >= 1; j--){

            std::string substring = word.substr(i, j);

            if (hashmap.find(substring) != hashmap.end() && substring.size() >3) {
                std::cout << substring << std::endl;
                return {i,j};
            }
        }
    }
    return {-1,-1};
}

std::string Wordle::findWord(const std::string& word) {
    for (int i = 0; i < (int)word.length(); i++){
        for (int j = word.length()-i; j >= 1; j--){

            std::string substring = word.substr(i, j);

            if (hashmap.find(substring) != hashmap.end() && substring.size() >3) {
                return word.substr(i,j);
            }
        }
    }
    return "";
}



