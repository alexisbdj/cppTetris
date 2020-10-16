/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Ultra
*/

#include "Ultra.hpp"

namespace Tetris {

Ultra::Ultra(sf::Font &font) : timeLeft(sf::seconds(180))
{
    score = 0;
    timeOver = false;

    scoreLabel.setFont(font);
    scoreText.setFont(font);
    scoreLabel.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    scoreLabel.setCharacterSize(20);
    scoreText.setCharacterSize(20);
    scoreLabel.setString("Score: ");
    scoreText.setString("0");
    scoreLabel.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));
    scoreText.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));

    timer.setFont(font);
    timer.setFillColor(sf::Color::White);
    timer.setCharacterSize(20);
    timer.setString(timeToStr(timeLeft));
    timer.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));
}

Ultra::~Ultra()
{
}

std::string Ultra::timeToStr(sf::Time time)
{
    std::string result;
    float sec = time.asSeconds();
    result += std::to_string((int) sec / 60);
    result += ":";
    result += std::to_string((int) sec % 60);
    return result;
}

void Ultra::render(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(scoreLabel);
    window.draw(scoreText);
    window.draw(timer);
}

void Ultra::lineCleared(int lines, bool isTspin, int combo, Environment &env)
{
    (void)env;
    if (combo > 1) {
        score += 50 * (combo - 1);
    }
    if (isTspin == false) {
        if (lines == 1)
            score += 100;
        if (lines == 2)
            score += 300;
        if (lines == 3)
            score += 500;
        if (lines >= 4)
            score += 800;
    }
    else {
        if (lines == 1)
            score += 800;
        if (lines == 2)
            score += 1200;
        if (lines >= 3)
            score += 1600;
    }
    scoreText.setString(std::to_string(score));
}

void Ultra::frameUpdate(sf::Time deltaTime)
{
    if (won())
        return;
    timeLeft -= deltaTime;
    if (timeLeft <= sf::seconds(0)) {
        timeLeft = sf::seconds(0);
        timeOver = true;
    }
    timer.setString(timeToStr(timeLeft));
    return;
}

bool Ultra::won()
{
    return timeOver;
}

void Ultra::setRenderPos(sf::Vector2f pos)
{
    background.setPrimitiveType(sf::PrimitiveType::Quads);
    background.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x + 10, pos.y), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x + 10, pos.y + 4), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 4), sf::Color(100, 100, 100)));
    scoreLabel.setPosition(sf::Vector2f(pos.x + 1, pos.y + 1));
    scoreText.setPosition(sf::Vector2f(pos.x + 3.5, pos.y + 1));
    timer.setPosition(sf::Vector2f(pos.x + 1, pos.y + 2));
}


}