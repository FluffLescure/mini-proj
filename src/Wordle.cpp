

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
std::vector<foundWord> Wordle::findWord(const std::string& word){
    std::vector<foundWord> foundWords;
    foundWord found;
    std::string r_word = word;

    for(int i = 0; i < (int)word.size(); i++)
        r_word[i] = word[word.size() -i -1];

    for (int i = 0; i < (int)word.length(); i++){
        for (int j = word.length() - i; j >= 1; j--){

            std::string substring = word.substr(i, j);

            if (hashmap.find(substring) != hashmap.end() && substring.size() >= 4) {
                std::cout << substring << i << " " << j <<std::endl;
                found.word = substring;
                found.position = {i,j};
                foundWords.push_back(found);
            }

        }
    }

     for (int i = (int)r_word.length(); i >= 0; i--){
        for (int j = 1; j < (int)r_word.length() - i; j++){

            std::string substring = r_word.substr(i, j);

            if (hashmap.find(substring) != hashmap.end() && substring.size() >= 4) {
                std::cout << substring << i << " " << j << std::endl;
                std::cout << (int)word.length() -1 -j << std::endl;
                std::cout << (int)word.size() -1 -i<< std::endl;

                found.word = substring;
                found.position = {(int)word.length()-i -j,j};
                foundWords.push_back(found);
            }

        }
    }


    return foundWords;
}



