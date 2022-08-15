#include <iostream>
#include <ctime>
#include <tuple>
#include <vector>
#include <limits>
#include "../include/game.hpp"
#include "../include/draw.hpp"

Game::Game()
{
    Init();
    for (int y = 0; y < ROWS; ++y)
    {
        for (int x = 0; x < COLUMNS; ++x)
        {
            cell[y * COLUMNS + x].state = State::CLOSED;
            cell[y * COLUMNS + x].hasMine = false;
            cell[y * COLUMNS + x].checked = false;
        }
    }

    srand(time(NULL));
    for (int i = 0; i < MINES; ++i)
    {
        int x, y;
        do
        {
            x = rand() % COLUMNS;
            y = rand() % ROWS;
        } while (cell[y * COLUMNS + x].hasMine);
        cell[y * COLUMNS + x].hasMine = true;
    }
}

Game::~Game()
{
    delete[] cell;
}

void Game::draw()
{
    Draw d;

    for (int y = 0; y < ROWS; ++y)
        for (int x = 0; x < COLUMNS; ++x)
        {
            switch (cell[y * COLUMNS + x].state)
            {
            case CLOSED:
                d.drawClosedCell(x, y);
                break;
            case OPENED:
                if (!cell[y * COLUMNS + x].hasMine)
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
                    d.gameOver();
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
    cell[y * COLUMNS + x].state = OPENED;
}

void Game::openAllMines()
{
    for (int y = 0; y < ROWS; ++y)
    {
        for (int x = 0; x < COLUMNS; ++x)
        {
            if (cell[y * COLUMNS + x].hasMine)
                cell[y * COLUMNS + x].state = State::OPENED;
        }
    }
}

void Game::flag(int x, int y)
{
    switch (cell[y * COLUMNS + x].state)
    {
    case OPENED:
        break;
    case CLOSED:
        cell[y * COLUMNS + x].state = FLAGGED;
        break;
    case FLAGGED:
        cell[y * COLUMNS + x].state = CLOSED;
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
            if (cell[yy * COLUMNS + xx].hasMine)
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
            if (!cell[y * COLUMNS + x].hasMine && cell[y * COLUMNS + x].state != State::CLOSED)
                count++;
        }
    }

    if ((ROWS * COLUMNS) - count == MINES)
        return true;

    return false;
}

void Game::openAdjacent(int x, int y)
{
    if (!inbounds(x, y))
        return;
    if (cell[y * COLUMNS + x].checked)
        return;
    if (cell[y * COLUMNS + x].hasMine)
        return;

    cell[y * COLUMNS + x].checked = true;
    cell[y * COLUMNS + x].state = State::OPENED;

    int minesAdjacent = numAdjacentMines(x, y);
    if (minesAdjacent > 0)
    {
        cell[y * COLUMNS + x].state = State::OPENED;
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

int Game::getRows()
{
    return ROWS;
}

int Game::getColumns()
{
    return COLUMNS;
}

void Game::Init()
{
    int level;

    std::cout << "\nWelcome to Minsweeper!!\n\n";

    std::cout << "The game has 3 different levels of difficulty from which to choose from, each with a different layout and number of mines.\n\n";

    std::cout << "They are:\n"
              << "\t- EASY    ==>  9 x 9 grid with 10 Mines\n\n"
              << "\t- HARD    ==>  16 x 16 grid with 40 Mines\n\n"
              << "\t- EXPERT  ==>  16 x 30 grid with 99 Mines\n\n";

    std::cout << "To choose your desired game difficulty:\n";
    std::cout << "\tPress 1 for EASY \n";
    std::cout << "\tPress 2 for HARD \n";
    std::cout << "\tPress 3 for EXPERT \n";

    while (true)
    {
        std::cout << "\nEnter difficulty level and press enter: ";

        std::cin >> level;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
        else if (level != 1 && level != 2 && level != 3)
        {
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    std::cout << "\nEnjoy!\n";

    if (level == EASY)
    {
        ROWS = 9;
        COLUMNS = 9;
        MINES = 10;
    }

    if (level == HARD)
    {
        ROWS = 16;
        COLUMNS = 16;
        MINES = 40;
    }

    if (level == EXPERT)
    {
        ROWS = 16;
        COLUMNS = 30;
        MINES = 99;
    }

    cell = new Cell[ROWS * COLUMNS];

    return;
}