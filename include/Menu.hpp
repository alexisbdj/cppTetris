/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include "Button.hpp"

namespace Tetris {

class Menu {
    public:
        enum Choice {
            LEAVE,
            SPRINT,
            MARATHON,
            ULTRA,
            UNKNOWN,
        };
        Menu(sf::RenderWindow &window, sf::Font &f);
        ~Menu();
        Choice run();
    private:
        void update(sf::Vector2i mousePos, bool clicked);
        void render();
        sf::RenderWindow &window;
        sf::Font &font;
        Choice choice;
        sf::View view;
        std::vector<Button> buttons;
        sf::Texture logoTexture;
        sf::VertexArray logoVarray;
};

}

#endif /* !MENU_HPP_ */
