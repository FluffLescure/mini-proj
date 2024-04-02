#include "../headers/GameDictionnary.hpp"


#include<iostream>
#include<fstream>
#include<vector>


Dictionnary::Dictionnary() {
    int size_ = 0;
    InitDictionnary();
}


void Dictionnary::InitDictionnary() {
    std::ifstream fich("resources/liste.txt");
    if (!fich.is_open()) std::cout << "Erreur d'ouverture" << std::endl;
    else {
        
        std::string word;

        while (fich >> word) { // Read words until end of file
            tab_.push_back(word);
            size_++;
        }

    }

}


bool Dictionnary::IsInside(std::string word) { //Not the definitive version but works
    for (int i = 0; i < size_; i++) {
        if (word == tab_[i]) return true;
    }
    return false;
}