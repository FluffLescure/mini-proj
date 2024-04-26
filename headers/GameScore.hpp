#ifndef GAME_SCORE_HPP
#define GAME_SCORE_HPP

#include<string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>



class GameScore {
private:

    // Bounding score frame 
    sf::RectangleShape scoreFrame_;

    //Text components
    sf::Text scoreVal_;
    sf::Text topScoreVal_;
    sf::Text scoreText_;
    sf::Text topScoreText_;

public:

    /**
     * @brief Constructor which calls the initialisation of components
    */
    GameScore();

    /**
     * @brief Initialises the frame of the object
    */
    void initFrame();

    /**
     * @brief Initialises the score text
    */
    void initText();

    /**
     * @brief Initialises the score value text
    */
    void initScore();

    /**
     * @brief Saves the score in a file 
    */
    ~GameScore();

    /**
     * @brief Retrieves the current score
     * @return the current score
    */
    const int getScore() const;

    /**
     * @brief Adds points to the score based on the length of the word given
     * @param word the word that needs to be scored
    */
    void addPoints(const std::string& word);

    /**
     * @brief Renders the score's bounding frame and text components
     * @param *target the rendered shared by other classes
    */
    void render(sf::RenderTarget *target) const;

};

#endif