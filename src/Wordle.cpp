

#include<iostream>

#include "../headers/Wordle.hpp"
#include "../headers/Config.hpp"

Wordle::Wordle() {
    initHashmap();
}

void Wordle::initHashmap() {
    int hash = 1; 
    //Assignes unique hash to each word from the wordlist
    for (std::string word : Config::getInstance()->wordlist)
        hashmap[word] = hash++;
    
}


//Needs optimisation
std::map<std::string, sf::Vector2i> Wordle::findWord(const std::string& word){
    std::map<std::string, sf::Vector2i> foundWords;
    std::string r_word = word;

    for(int i = 0; i < (int)word.size(); i++)
        r_word[i] = word[(word.size() - 1) - i];

    for (int i = 0; i < (int)word.length(); i++){
        for (int length = word.length() - i; length >= 1; length--){

            std::string substring = word.substr(i, length);

            if (hashmap.find(substring) != hashmap.end() && substring.size() >= 4) 
                foundWords.emplace(std::pair(substring, sf::Vector2i(i, length)));
            

        }
    }

     for (int i = (int)r_word.length(); i >= 0; i--){
        for (int j = 1; j < (int)r_word.length() - i; j++){

            std::string substring = r_word.substr(i, j);

            if (hashmap.find(substring) != hashmap.end() && substring.size() >= 4) 
                foundWords.emplace(std::pair(substring, sf::Vector2i((int)word.size() - i - j, j)));
            
        }
    }


    return foundWords;
}



