#ifndef INPUT_HPP
#define INPUT_HPP


enum Direction {
    Unchanged, Down, Left, Right
};


class Input {
private:
    Direction direction;

public:
    void pollEvent();

    Direction getDirection() { return direction; }
};

#endif