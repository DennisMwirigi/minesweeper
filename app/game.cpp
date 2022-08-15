#include <iostream>
#include <ctime>
#include "../include/game.hpp"
#include "../include/draw.hpp"

Game::Game()
{
    for (int y = 0; y < ROWS; ++y)
    {
        for (int x = 0; x < COLUMNS; ++x)
        {
            cell[x][y].state = State::CLOSED;
            cell[x][y].hasMine = false;
        }
    }

    srand(time(NULL));
    for (int i = 0; i < 10; ++i)
    {
        int x, y;
        do
        {
            x = rand() % COLUMNS;
            y = rand() % ROWS;
        } while (cell[x][y].hasMine);
        cell[x][y].hasMine = true;
    }
}

void Game::draw()
{
    Draw d;

    for (int y = 0; y < ROWS; ++y)
        for (int x = 0; x < COLUMNS; ++x)
        {
            switch (cell[x][y].state)
            {
            case CLOSED:
                d.drawClosedCell(x, y);
                break;
            case OPENED:
                if (!cell[x][y].hasMine)
                {
                    int minesAdjacent = 0;
                    for (int yy = y - 1; yy <= y + 1; ++yy)
                        for (int xx = x - 1; xx <= x + 1; ++xx)
                        {
                            if ((xx == x && yy == y) ||
                                xx < 0 || xx >= COLUMNS ||
                                yy < 0 || yy >= ROWS)
                                continue;
                            if (cell[xx][yy].hasMine)
                                ++minesAdjacent;
                        }
                    d.drawOpenCellNumMines(x, y, minesAdjacent);

                    if (checkWin())
                        d.gameWin();
                }
                else
                {
                    d.drawMine(x, y);
                    openAllMines();
                    d.gameOver(ROWS, COLUMNS);
                }
                break;
            case FLAGGED:
                d.drawFlag(x, y);
                break;
            }
        }
}

void Game::open(int x, int y)
{
    cell[x][y].state = OPENED;
}

void Game::openAllMines()
{
    for (int y = 0; y < ROWS; ++y)
    {
        for (int x = 0; x < COLUMNS; ++x)
        {
            if (cell[x][y].hasMine)
                cell[x][y].state = State::OPENED;
        }
    }
}

void Game::flag(int x, int y)
{
    switch (cell[x][y].state)
    {
    case OPENED:
        break;
    case CLOSED:
        cell[x][y].state = FLAGGED;
        break;
    case FLAGGED:
        cell[x][y].state = CLOSED;
        break;
    }
}

bool Game::checkWin()
{
    int count = 0;
    for (int y = 0; y < ROWS; ++y)
    {
        for (int x = 0; x < COLUMNS; ++x)
        {
            if (!cell[x][y].hasMine && cell[x][y].state != State::CLOSED)
                count++;
        }
    }

    if ((ROWS * COLUMNS) - count == 10)
        return true;

    return false;
}