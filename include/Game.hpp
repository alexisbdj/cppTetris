/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "GameMode.hpp"

namespace Tetris {

class Game {
    public:
        Game();
        ~Game();

        int run();
        void pollEvent();

    private:
        Menu::Choice getChoice();
        void startGame(GameMode &gamemode);
        sf::RenderWindow window;
        sf::Font font;
        sf::View view;
        bool didInitSuccessfully;
};

}

#endif /* !GAME_HPP_ */
