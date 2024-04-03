#include "../headers/Dictionary.hpp"


#include<iostream>
#include<fstream>
#include<vector>


Dictionary::Dictionary() {
    initDictionnary();
    initHashmap();
}




void Dictionary::initDictionnary() {
    std::ifstream file("resources/liste.txt");
    if (!file.is_open())
        abort();
    
        
    std::string word;
    
    //reads words from file and converts them to uppercase
    while (file >> word) { 
        for(char &c : word)
            c = std::toupper(c);
        dictionary.push_back(word);
    }
    
}

void Dictionary::initHashmap() {
    int counter = 1; 
    //Assignes unique hash to each word
    for (std::string word : dictionary) {
        hashmap[word] = counter++;
    }
}

sf::Vector2u Dictionary::foundHash(const std::string& word) {
    for (unsigned int i = 0; i < word.length(); i++){
        for (unsigned int j = 1; i + j <= word.length(); j++){

             std::string substring = word.substr(i, j);

            if (hashmap.find(substring) != hashmap.end() && substring .size() > 1) {
                return {i,j};
            }
        }
    }
    return {0,0};
}




