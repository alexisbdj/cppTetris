/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** TimeConversion
*/

#include "TimeConversion.hpp"

namespace Tetris {
    Tetris::Time sfmlToGenericTime(sf::Time &source)
    {
        return Tetris::microseconds(source.asMicroseconds());
    }
}