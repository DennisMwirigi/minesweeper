#pragma once

#define EASY 0
#define HARD 1
#define EXPERT 2

class Game
{
public:
    enum State
    {
        CLOSED,
        OPENED,
        FLAGGED
    };

    Game();
    ~Game();
    void draw();
    void open(int x, int y);
    void openAllMines();
    void flag(int x, int y);
    int numAdjacentMines(int x, int y);
    bool checkWin();
    void openAdjacent(int x, int y);
    bool inbounds(int x, int y);
    int getRows();
    int getColumns();
    void Init();

private:
    int ROWS;
    int COLUMNS;
    int MINES;

    struct Cell
    {
        State state;
        bool hasMine;
        bool checked;
    };

    Cell *cell;
};