/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** GameMode
*/

#ifndef GAMEMODE_HPP_
#define GAMEMODE_HPP_

#include <SFML/Graphics.hpp>


namespace Tetris {

class Environment;

class GameMode {
    public:
        virtual void render(sf::RenderWindow &window) = 0;
        virtual void lineCleared(int lines, bool isTspin, int combo, Environment &env) = 0;
        virtual void frameUpdate(sf::Time deltaTime) = 0;
        virtual bool won() = 0;
        virtual void setRenderPos(sf::Vector2f pos) = 0;
};

}

#endif /* !GAMEMODE_HPP_ */
