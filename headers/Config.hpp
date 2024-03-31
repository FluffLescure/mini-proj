#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>


//Macro of a map of Vector2f which has been named vec2 for legibility reasons
typedef std::vector<sf::Vector2f> vec2;


/**
 * @class Config
 * @brief A singleton that stores global configurations of the game in manner that
 *  allows it to share these configurations with other classes without needing to
 *  be inherited.
 * 
 * @note This class is meant to be called through its shared static 'instance' member
 * 
 * @remark This allows the configurations, such as textures and layout, to be loaded
 *  only once instead of needing to be called at every initialisation.
 * 
 * Furthermore it also improves code legiblity by centralising global configs in one
 * place, and avoids cluttering classes with too many constant members.
 * 
 * The class is a unique element that can not be copied or reconstructed as per its 
 * use as a singleton.
 * 
 * It can be called by retrieving the instance of the class using the getInstance()
 * method.  This can then be stored, if needed in a class pointer for multiple 
 * configuration calls.
 * 
 * @code 
 * // Stores the instance in a 'config' pointer
 * Config* config = Config::getInstance();
 * 
 * // Used more multiple config calls 
 * printf("Title: %s \nFramerate: %d",config->window_title, config->window_framerate);
 * 
 * // Used as a single call without storing to a pointer
 * Vector2i Size = Config::getInstance()->window_size; 
 * @endcode
 *  
*/
class Config {
private:
    /** 
     * Stores a single instance of the class to access class configs and
     * resources.
     * The static descriptor allows it to be accessible outside the object
    */ 
    static Config *instance;

    /**
     * @brief Constructor which loads each resource.  
    */
    Config();

    /**
     * @brief Loads textures for the layoutTex member using the texture_file.
     * This is then used to add a texture to the layout in GameDisplay. 
    */
    void loadTextures();

    /**
     * @brief Loads the font for sf::Text components used to display text in-game
    */
    void loadFonts();

    /**
     * @brief Loads the layout for the layoutPoints member using the layout_file.
     * This is then used to render the layout in GameDisplay. 
    */
    void loadLayout();

    // Ressources file path 
    const std::string font_file = "resources/Lato-Black.ttf";
    const std::string texture_file = "resources/background_texture.jpg";
    const std::string layout_file = "resources/layout.map";
    
public:

    /**
     * @brief Allows access to configs and resources by retrieving an instance of
     * the Class.
     * @returns A Config pointer to access configs
    */
    static Config* getInstance();

    // Deletion of copy constructors as per its singleton property.
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    // Frees font and layoutTex from memory.
    ~Config();

    // Global configs of the game
    const sf::Vector2i window_size = {960, 540};
    const int window_framerate = 60;
    const sf::Vector2f block_size = {33.6, 32.4};
    const std::string window_title = "Lettris";
    const uint8_t gamegrid_rows = 15;
    const uint8_t gamegrid_cols = 10;

    // Preloaded resources of the game
    sf::Font *font;
    sf::Texture *layoutTex;
    vec2 layoutPoints;
};



#endif