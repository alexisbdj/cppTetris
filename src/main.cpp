/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** main
*/

#include "Game.hpp"
#include "WallKick.hpp"

int main()
{
    srand(time(0));
    Tetris::Game game;
    return game.run();
}