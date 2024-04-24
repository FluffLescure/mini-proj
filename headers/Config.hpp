#ifndef CONFIG_HPP
#define CONFIG_HPP

#include<stdint.h>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>




/**
 * @class Config
 * @brief A singleton that stores global configurations of the game in manner that
 *  allows it to share these configurations with other classes externally without
 *  requiring an explicit relationship.
 * 
 * @note This class is meant to be called through its shared and static instance
 * 
 * @remark This allows the configs, such as textures and layout, to be loaded
 *  only once instead of needing to be called at every initialisation.
 * 
 * Furthermore it also improves code legiblity by storing global configs in one
 * place which avoids cluttering classes with too many constant members.
 * 
 * The class is a unique in that it can not be copied or reconstructed since it 
 * functions as a singleton.
 * 
 * It can be called by retrieving the instance of the class using the getInstance()
 * method.  This can then be stored, in a class pointer for multiple configuration
 * calls.
 * 
 * @code 
 * // Stores the instance in a 'config' pointer for repeated parameter calls
 * Config* config = Config::getInstance();
 * 
 * // Config's shared member are acccessed using the instance pointer 
 * printf("Title: %s \nFramerate: %d",config->window_title, config->window_framerate);
 * 
 * // Used for single calls without requiring a pointer to store the instance
 * Vector2i Size = Config::getInstance()->window_size; 
 * @endcode
 *  
*/
class Config {
private:
    /** 
     * Stores a single instance of the class to access class configs and
     * resources.
     * The static descriptor allows it to be accessible outside the object scope
    */ 
    static Config *instance;

    /**
     * @brief Constructor which loads each resource. 
     * @remark Is defined as a private method to avoid creating multiple instances. 
    */
    Config();

     /**
     * @brief Loads the font for sf::Text components used to display in-game text
    */
    void loadFonts();

    /**
     * @brief Loads textures for the layoutTex member using the texture_file.
     * This is then used to add a texture to the layout. 
    */
    void loadTextures();

    /**
     * @brief Loads the layout for the layoutPoints member using the layout_file.
     * This is then used to render the layout in GameDisplay. 
    */
    void loadLayout();

    /**
     * @brief Loads the wordlist which will be used to identify words contained in the grid.
    */
    void loadWordlist();


    // Resources file path 
    const std::string font_file = "resources/Lato-Black.ttf";
    const std::string texture_file = "resources/background_texture.jpg";
    const std::string layout_file = "resources/layout.map";
    const std::string wordlist_file = "resources/wordlist.txt";
    
    
    
    
public:

    /**
     * @brief Allows access to configs and resources by retrieving the current instance of
     * the class.
     * @returns A Config pointer to access config parameters
    */
    static Config* getInstance();

    // Deletion of copy constructors according to singleton properties.
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    // Frees font and layout texture from memory.
    ~Config();

    // Global configs of the game
    const sf::Vector2i window_size = {960, 540};
    const int window_framerate = 60;
    const sf::Vector2f block_size = {33.6, 32.4};
    const std::string window_title = "Lettris";
    const uint8_t gamegrid_rows = 15;
    const uint8_t gamegrid_cols = 10;
    const std::vector<int>generator_weights = {711, 114, 318, 367, 1210, 111, 123, 111, 659, 34, 29, 496, 262, 639, 502, 249, 65, 607, 651, 592, 449, 111, 17, 38, 46, 15};
    const std::string scores_file = "resources/Scores.txt";
    const std::string colorscheme_file = "resources/colorscheme.theme";
    

    // Storage of game resources
    sf::Font *font;
    sf::Texture *layoutTex;
    std::vector<sf::Vector2f> layoutPoints;
    std::vector<std::string> wordlist;
    std::map<std::string, sf::Color> colorScheme;
};



#endif