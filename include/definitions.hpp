#pragma once

struct Level
{
    struct EASY
    {
        const int ROWS = 9;
        const int COLUMNS = 9;
        const int MINES = 10;
    };

    struct HARD
    {
        const int ROWS = 16;
        const int COLUMNS = 16;
        const int MINES = 40;
    };

    struct EXPERT
    {
        const int ROWS = 16;
        const int COLUMNS = 30;
        const int MINES = 99;
    };

    EASY easy;
    HARD hard;
    EXPERT expert;
};

static const int CELL_SIZE = 16;
