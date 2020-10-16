/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <string>

namespace Tetris {

class Button {
    public:
        Button(sf::FloatRect rect, sf::Font &font, const std::string &text);
        ~Button();
        void render(sf::RenderWindow &window);
        bool isClicked(sf::Vector2i mousePos);
    private:
        sf::FloatRect pos;
        sf::Text text;
        sf::VertexArray background;

};

}

#endif /* !BUTTON_HPP_ */
