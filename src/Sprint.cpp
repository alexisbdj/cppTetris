/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Sprint
*/

#include "Sprint.hpp"

namespace Tetris {

Sprint::Sprint(sf::Font &font) : linesLeft(40)
{
    linesLabel.setFont(font);
    linesText.setFont(font);
    linesLabel.setFillColor(sf::Color::White);
    linesText.setFillColor(sf::Color::White);
    linesLabel.setCharacterSize(20);
    linesText.setCharacterSize(20);
    linesLabel.setString("Lines: ");
    linesText.setString(std::to_string(linesLeft));
    linesLabel.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));
    linesText.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));

    currentTime = sf::seconds(0);

    timer.setFont(font);
    timer.setFillColor(sf::Color::White);
    timer.setCharacterSize(20);
    timer.setString(timeToStr(currentTime));
    timer.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));
}

Sprint::~Sprint()
{
}

std::string Sprint::timeToStr(sf::Time time)
{
    std::string result;
    float sec = time.asSeconds();
    result += std::to_string((int) sec / 60);
    result += ":";
    result += std::to_string((int) sec % 60);
    return result;
}

void Sprint::render(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(linesLabel);
    window.draw(linesText);
    window.draw(timer);
}

void Sprint::lineCleared(int lines, bool isTspin, int combo, Environment &env)
{
    (void)isTspin;
    (void)combo;
    (void)env;
    linesLeft = std::max(linesLeft - lines, 0);

    linesText.setString(std::to_string(linesLeft));
}

void Sprint::frameUpdate(sf::Time deltaTime)
{
    currentTime += deltaTime;
    timer.setString(timeToStr(currentTime));
}

bool Sprint::won()
{
    return linesLeft == 0;
}

void Sprint::setRenderPos(sf::Vector2f pos)
{
    background.setPrimitiveType(sf::PrimitiveType::Quads);
    background.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x + 10, pos.y), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x + 10, pos.y + 4), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 4), sf::Color(100, 100, 100)));
    linesLabel.setPosition(sf::Vector2f(pos.x + 1, pos.y + 1));
    linesText.setPosition(sf::Vector2f(pos.x + 3.5, pos.y + 1));
    timer.setPosition(sf::Vector2f(pos.x + 1, pos.y + 2));
}

}