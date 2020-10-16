/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** WallKick
*/

#include <iostream>
#include "WallKick.hpp"

namespace Tetris {

const sf::Vector2i WallKick::normalTable[4][5] = {
    {   // stat 0
        {0, 0},   //offset 0-1
        {0, 0},   //offset 0-2
        {0, 0},   //offset 0-3
        {0, 0},   //offset 0-4
        {0, 0},   //offset 0-5
    },
    {   //stat 1 (R)
        {0, 0},   //offset 1-1
        {1, 0},   //offset 1-2
        {1, -1},   //offset 1-3
        {0, 2},   //offset 1-4
        {1, 2},   //offset 1-5
    },
    {   //stat 2
        {0, 0},   //offset 2-1
        {0, 0},   //offset 2-2
        {0, 0},   //offset 2-3
        {0, 0},   //offset 2-4
        {0, 0},   //offset 2-5
    },
    {   //stat 3 (L)
        {0, 0},   //offset 3-1
        {-1, 0},   //offset 3-2
        {-1, -1},   //offset 3-3
        {0, 2},   //offset 3-4
        {-1, 2},   //offset 3-5
    },
};

const sf::Vector2i WallKick::iPieceTable[4][5] = {
    {   // stat 0
        {0, 0},   //offset 0-1
        {-1, 0},   //offset 0-2
        {2, 0},   //offset 0-3
        {-1, 0},   //offset 0-4
        {2, 0},   //offset 0-5
    },
    {   //stat 1 (R)
        {-1, 0},   //offset 1-1
        {0, 0},   //offset 1-2
        {0, 0},   //offset 1-3
        {0, 1},   //offset 1-4
        {0, -2},   //offset 1-5
    },
    {   //stat 2
        {-1, 1},   //offset 2-1
        {1, 1},   //offset 2-2
        {-2, 1},   //offset 2-3
        {1, 0},   //offset 2-4
        {-2, 0},   //offset 2-5
    },
    {   //stat 3 (L)
        {0, 1},   //offset 3-1
        {0, 1},   //offset 3-2
        {0, 1},   //offset 3-3
        {0, -1},   //offset 3-4
        {0, 2},   //offset 3-5
    },
};

WallKick::WallKick()
{
}

sf::Vector2i WallKick::getOffset(Table table, int stat, int index)
{
    if (table == NORMAL) {
        return WallKick::normalTable[stat][index];
    }
    return WallKick::iPieceTable[stat][index];
}

WallKick::~WallKick()
{
}

}