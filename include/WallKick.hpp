/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** WallKick
*/

#ifndef WALLKICK_HPP_
#define WALLKICK_HPP_

#include <SFML/System.hpp>

namespace Tetris {

class WallKick {
    public:
        enum Table {
            NORMAL,
            IPIECE,
        };
        WallKick();
        ~WallKick();
        sf::Vector2i getOffset(Table table, int stat, int index);
    protected:
        static const sf::Vector2i normalTable[4][5];
        static const sf::Vector2i iPieceTable[4][5];
};

}

#endif /* !WALLKICK_HPP_ */
