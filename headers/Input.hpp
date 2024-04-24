#ifndef INPUT_HPP
#define INPUT_HPP

/**
* @enum Direction
* @brief Possible movement directions used to move the falling block in GameGrid
*/
enum Direction {
    Unchanged, Down, Left, Right
};


/**
* @class Input
* @brief Retrieval of user input to memory 
* @remark This class polls events that happen on window with the method pollEvent()
* and stores the input to member direction. The direction of the input can then be
* retrieved using the getDirection() method
*/
class Input {
private:
    // input direction
    Direction direction = Direction::Unchanged;

public:
    /**
    * @brief Polls arrow key events and stores them to 'direction' 
    */
    void pollEvent();

    int inputTick(bool keepTicking = true);


    /**
    * @brief Returns the stored direction from input
    * @returns The direction of the input  
    */
    Direction getDirection() { return direction; }
};

#endif