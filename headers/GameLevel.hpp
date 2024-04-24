#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include<map>
#include<string>

#include <SFML/Graphics/Color.hpp>

class GameLevel {
private:
    const int levelSpeed[10] = {5, 4, 4, 3, 3, 3, 2, 2, 2, 2};
    int speed;
    std::map<std::string, sf::Color> colorScheme[4];
public:
    GameLevel();

    void initColorschemes();

    int getSpeed() const;

    void levelUp();

};



#endif