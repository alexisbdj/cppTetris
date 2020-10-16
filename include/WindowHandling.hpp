/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** WindowHandling
*/

#ifndef WINDOWHANDLING_HPP_
#define WINDOWHANDLING_HPP_

#include <SFML/Graphics.hpp>
#include "GameMode.hpp"
#include "Graphical.hpp"

namespace Tetris {

class WindowHandling {
    public:
        WindowHandling(sf::RenderWindow &win, GameMode &gamemode, sf::Font &font);
        ~WindowHandling();

        void run();
    protected:
    private:
        void processEvent();
        void update(sf::Time deltaTime);
        void handleActions(Tetris::Environment &env, sf::Event &event);
        Graphical graph;
        Environment env;
        sf::RenderWindow &window;
        GameMode &gamemode;
        sf::Text mainText;
        sf::Text howToLeave;
        bool isOver ;
        bool left ;
        bool pressedEnter;
};

}

#endif /* !WINDOWHANDLING_HPP_ */
