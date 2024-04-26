#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include<map>
#include<string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class GameLevel {
private:
    const int levelSpeed[10] = {5, 4, 4, 3, 3, 3, 2, 2, 2, 2};
    int speed;
    std::map<std::string, sf::Color> colorScheme[4];

    sf::RectangleShape stageFrame;
    sf::RectangleShape levelFrame;

    sf::Text levelText;
    sf::Text stageText;

public:
    GameLevel();

    void initColorschemes();
    void initFrames();
    void initText();

    int getSpeed() const { return speed; }

    void levelUp();

    void render(sf::RenderTarget *target);

};



#endif