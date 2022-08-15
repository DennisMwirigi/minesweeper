#pragma once

class Draw
{
public:
    void drawClosedCell(int x, int y);
    void drawOpenCell(int x, int y, float *cellColor);
    void drawOpenCellNumMines(int x, int y, int minesAdjacent);
    void drawFlag(int x, int y);
    void drawMine(int x, int y);
    void gameOver(int rows, int columns);
    void gameWin();
    void drawText(const char *text, int x = 0, int y = 0, int z = 0);
};