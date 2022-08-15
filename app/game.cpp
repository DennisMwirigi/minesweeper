#include <ctime>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

#include "../include/game.hpp"
#include "../include/draw.hpp"

// game constructor
Game::Game()
{
    setDifficulty(); // take user input defining their difficulty of choice to play with
    Init(); // initialise game board
}

// game destructor
Game::~Game()
{
    delete[] cell; // free dynamically allocated memory
}

// render game board
void Game::draw()
{
    Draw d;

    // loop over all cells
    for (int y = 0; y < ROWS; ++y)
        for (int x = 0; x < COLUMNS; ++x)
        {
            switch (cell[y * COLUMNS + x].state)
            {
            case CLOSED:
                // render closed cell image
                d.drawClosedCell(x, y);
                break;
            case OPENED:
                if (!cell[y * COLUMNS + x].hasMine)
                {
                    int minesAdjacent = numAdjacentMines(x, y); // determine hint to be displayed to user
                    d.drawOpenCellNumMines(x, y, minesAdjacent); // display hint

                    // if minesAdjacent == 0
                    if (!minesAdjacent)
                        openAdjacent(x, y); // recursively open adjacent cells to cell containing no mines adjacent to it

                    // after opening a cell, check if win condition has been satisfied
                    if (checkWin())
                        d.gameWin(); // if yes, end game by winning
                }
                else // if opened cell contains a mine
                {
                    // render mine image on clicked cell
                    d.drawMine(x, y);

                    // reveal location of all other mines
                    openAllMines();

                    // end game due to uncovering a mine
                    d.gameOver();
                }
                break;
            case FLAGGED:
                // render flag image over clicked cell
                d.drawFlag(x, y);
                break;
            }
        }
}

// set state of cell to OPENED
void Game::open(int x, int y)
{
    cell[y * COLUMNS + x].state = OPENED;
}

// set state of all mine cells to OPENED
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

// set state of cell to flagged; close cell if previously flagged
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

// count the number of mines adjacent to cell
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

// determine if win condition is satisfied
bool Game::checkWin()
{
    // win condition: every cell not containing a mine has been opened
    int count = 0;
    for (int y = 0; y < ROWS; ++y)
    {
        for (int x = 0; x < COLUMNS; ++x)
        {
            // count number of opened cells not containing mines
            if (!cell[y * COLUMNS + x].hasMine && cell[y * COLUMNS + x].state != State::CLOSED)
                count++;
        }
    }

    // if remaining number of unopened cells equals number of mines, You Win !
    if ((ROWS * COLUMNS) - count == MINES)
        return true;

    return false;
}

// recursively open non-mine adjacent cells
void Game::openAdjacent(int x, int y)
{
    // 3 base cases:

    // cell is within game board 
    // the recursion may end up going off the laid out grid and would result in errors
    if (!inbounds(x, y))
        return;

    // check if cell has been visited already, if yes, skip over it
    // prevents infinte recursive calls
    if (cell[y * COLUMNS + x].checked)
        return;

    // check if cell has a mine, if yes, stop recursing in that direction
    if (cell[y * COLUMNS + x].hasMine)
        return;


    // set cell as visited during recursion then open up the cell
    cell[y * COLUMNS + x].checked = true;
    cell[y * COLUMNS + x].state = State::OPENED;

    // also open hint cells
    int minesAdjacent = numAdjacentMines(x, y);
    if (minesAdjacent > 0)
    {
        cell[y * COLUMNS + x].state = State::OPENED;
        return;
    }

    // all poosible adjacent positions to recursively check, relative to current cell

    //              (-1, -1)     (0, -1)     (1, -1)
    //                   \          |          /
    //                    \         |         /
    //                              
    //       (-1, 0)  –– ––   current cell   –– ––  (1, 0)
    //
    //                     /        |         \
    //                    /         |          \
    //                (-1, 1)     (0, 1)      (1, 1)
    std::vector<std::tuple<int, int>> adjacentCells{std::tuple<int, int>{0, 1},
                                                    std::tuple<int, int>{0, -1},
                                                    std::tuple<int, int>{1, 0},
                                                    std::tuple<int, int>{-1, 0},
                                                    std::tuple<int, int>{1, 1},
                                                    std::tuple<int, int>{1, -1},
                                                    std::tuple<int, int>{-1, 1},
                                                    std::tuple<int, int>{-1, -1}};

    // recurse through all positions
    for (std::vector<std::tuple<int, int>>::iterator i = adjacentCells.begin(); i != adjacentCells.end(); ++i)
    {
        openAdjacent(x + std::get<0>(*i), y + std::get<1>(*i));
    }
}

// check if x, y position is within bounds of game board
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

// take user input to determine the level of difficulty they wish to play with
void Game::setDifficulty()
{
    int level; // 1 - Easy, 2 - Hard, 3 - Expert

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

    std::cout << "\n## Please Note ##\n"
              << "\tWhile playing the game, clicking on any of the following keys will cause the corresponding events to occur:\n"
              << "\t\t- Q key ==> Quits the game and closes the game window\n"
              << "\t\t- R key ==> Restarts the current level\n";

    // handle invalid user input
    while (true) // until user input is valid or program is terminated
    {
        std::cout << "\nEnter difficulty level and press enter: ";

        std::cin >> level;

        // if user input is not of correct type
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // extract any remaining characters in stream and discard them
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
        // if user input is of correct type i.e int, but not any of the valid options
        else if (level != 1 && level != 2 && level != 3)
        {
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
        // if input is valid
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // extract any remaining characters in stream and discard them
            break;
        }
    }

    std::cout << "\nEnjoy!\n";

    // set values to be used by the game
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

    // allocate memory for entire grid in a 1d array that simulates a 2d array
    cell = new Cell[ROWS * COLUMNS];

    return;
}

// initialise game board
void Game::Init()
{
    // for all cells
    for (int y = 0; y < ROWS; ++y)
    {
        for (int x = 0; x < COLUMNS; ++x)
        {
            cell[y * COLUMNS + x].state = State::CLOSED;
            cell[y * COLUMNS + x].hasMine = false;
            cell[y * COLUMNS + x].checked = false;
        }
    }

    // randomly place mines all over grid
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