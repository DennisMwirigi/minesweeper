#pragma once
// #include "definitions.hpp"

// auto level = Level::EASY;

// int rows = level.ROWS;

class Draw
{
public:
    int ROWS = 9, COLUMNS = 9, CELL_SIZE = 16;

    void drawClosedCell(int x, int y);
    void drawOpenCell(int x, int y);
    void drawFlag(int x, int y);
    void drawMine(int x, int y);

    void drawBoard();
};