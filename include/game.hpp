#pragma once
// #include "definitions.hpp"

// static Level l;
// const static auto level = l.easy;

class Game
{
public:
    enum State
    {
        CLOSED,
        OPENED,
        FLAGGED
    };

    enum
    {
        ROWS = 9,
        COLUMNS = 9
    };

    Game();
    void draw();
    void open(int x, int y);
    void flag(int x, int y);

private:
    struct Cell
    {
        State state;
        bool hasMine;
    };
    Cell cell[COLUMNS][ROWS];
};