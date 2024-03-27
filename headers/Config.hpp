#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>

typedef std::vector<sf::Vector2f> vec2;

class Config {

private:
    static Config *instance;
    Config();

    void loadTextures();
    void loadFonts();
    void loadLayout();

    const std::string font_file = "ressources/Lato-Black.ttf";
    const std::string texture_file = "ressources/background_texture.jpg";
    const std::string layout_file = "ressources/layout.map";
    


public:
    static Config *getInstance();
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    ~Config();

    const sf::Vector2i window_size = {960, 540};
    const int window_framerate = 60;
    const sf::Vector2f block_size = {33.2, 32.6};
    const std::string window_title = "Lettris";

    sf::Font *font;
    sf::Texture *layoutTex;
    vec2 layoutPoints;



};



#endif