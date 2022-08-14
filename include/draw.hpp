#pragma once

class Draw
{
public:
    // int CELL_SIZE = 16;

    void drawClosedCell(int x, int y);
    void drawOpenCell(int x, int y);
    void drawOpenCellNumMines(int x, int y, int minesAdjacent);
    void drawFlag(int x, int y);
    void drawMine(int x, int y);
};