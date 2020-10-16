/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Button
*/

#include "Button.hpp"

namespace Tetris {

Button::Button(sf::FloatRect rect, sf::Font &font, const std::string &textstr) : pos(rect)
{
    background.setPrimitiveType(sf::PrimitiveType::Quads);
    sf::Vertex vertex(sf::Vector2f(rect.left, rect.top), sf::Color(100, 100, 100));
    background.append(vertex);
    vertex.position.x += rect.width;
    background.append(vertex);
    vertex.position.y += rect.height;
    background.append(vertex);
    vertex.position.x -= rect.width;
    background.append(vertex);
    text.setPosition(sf::Vector2f(rect.left, rect.top));
    text.setString(textstr);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
}

Button::~Button()
{
}

void Button::render(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(text);
}

bool Button::isClicked(sf::Vector2i mousePos)
{
    return (mousePos.x > pos.left && mousePos.x < (pos.left + pos.width) &&
        mousePos.y > pos.top && mousePos.y < (pos.top + pos.height));
}

}