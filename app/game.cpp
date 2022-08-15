#include <iostream>
#include <ctime>
#include <tuple>
#include <vector>
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
                    int minesAdjacent = numAdjacentMines(x, y);
                    d.drawOpenCellNumMines(x, y, minesAdjacent);

                    if (!minesAdjacent)
                        openAdjacent(x, y);

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

int Game::numAdjacentMines(int x, int y)
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

    return minesAdjacent;
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

void Game::openAdjacent(int x, int y)
{
    if (!inbounds(x, y))
        return;
    if (cell[x][y].checked)
        return;
    if (cell[x][y].hasMine)
        return;

    cell[x][y].checked = true;
    cell[x][y].state = State::OPENED;

    int minesAdjacent = numAdjacentMines(x, y);
    if (minesAdjacent > 0)
    {
        cell[x][y].state = State::OPENED;
        return;
    }

    std::vector<std::tuple<int, int>> adjacentCells{std::tuple<int, int>{0, 1},
                                                    std::tuple<int, int>{0, -1},
                                                    std::tuple<int, int>{1, 0},
                                                    std::tuple<int, int>{-1, 0},
                                                    std::tuple<int, int>{1, 1},
                                                    std::tuple<int, int>{1, -1},
                                                    std::tuple<int, int>{-1, 1},
                                                    std::tuple<int, int>{-1, -1}};

    for (std::vector<std::tuple<int, int>>::iterator i = adjacentCells.begin(); i != adjacentCells.end(); ++i)
    {
        openAdjacent(x + std::get<0>(*i), y + std::get<1>(*i));
    }
}

bool Game::inbounds(int x, int y)
{
    if (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS)
        return true;

    return false;
}