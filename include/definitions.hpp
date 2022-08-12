#pragma once

class Level
{
    enum class EASY
    {
        ROWS = 9,
        COLUMNS = 9,
        MINES = 10,
    };

    enum class HARD
    {
        ROWS = 16,
        COLUMNS = 16,
        MINES = 40,
    };

    enum class EXPERT
    {
        ROWS = 16,
        COLUMNS = 30,
        MINES = 99,
    };
};
