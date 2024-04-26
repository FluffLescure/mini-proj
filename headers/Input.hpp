#ifndef INPUT_HPP
#define INPUT_HPP

/**
* @enum Direction
* @brief Possible movement directions used to move the falling block in GameGrid
*/
enum Direction {
    Unchanged, Down, Left, Right, Space
};


/**
* @class Input
* @brief Retrieval of user input to memory 
* @remark This class polls events that happen on window with the method pollEvent()
* and stores the input to member direction. The direction of the input can then be
* retrieved using the getInput() method
*/
class Input {
private:
    // input direction
    Direction input_ = Direction::Unchanged;

public:
    /**
    * @brief Polls arrow key events and stores them to 'direction' 
    */
    void pollEvent();


    /**
     * @brief Keeps the value of the input for a duration of 5 ticks
     * @param keepTicking determines if the counter should keep ticking
     * @returns The value of the counter;
    */
    const int inputTick(const bool& keepTicking = true);


    /**
    * @brief Returns the stored direction from input
    * @returns The direction of the input  
    */
    const Direction& getInput() const { return input_; }
};

#endif