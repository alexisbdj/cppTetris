/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Marathon
*/

#include <iostream>
#include "Environment.hpp"
#include "Marathon.hpp"

namespace Tetris {

Marathon::Marathon(sf::Font &font) : score(0)
{
    level = 1;
    clearedLines = 0;
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

    levelLabel.setFont(font);
    levelText.setFont(font);
    levelLabel.setFillColor(sf::Color::White);
    levelText.setFillColor(sf::Color::White);
    levelLabel.setCharacterSize(20);
    levelText.setCharacterSize(20);
    levelLabel.setString("level: ");
    levelText.setString("1");
    levelLabel.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));
    levelText.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));
}

Marathon::~Marathon()
{
}

void Marathon::render(sf::RenderWindow &window)
{
    window.draw(background);
    window.draw(scoreLabel);
    window.draw(scoreText);
    window.draw(levelLabel);
    window.draw(levelText);

}

void Marathon::lineCleared(int lines, bool isTspin, int combo, Environment &env)
{
    clearedLines += lines;
    if (combo > 1) {
        score += 50 * (combo - 1) * level;
    }
    if (isTspin == false) {
        if (lines == 1)
            score += 100 * level;
        if (lines == 2)
            score += 300 * level;
        if (lines == 3)
            score += 500 * level;
        if (lines >= 4)
            score += 800 * level;
    }
    else {
        if (lines == 1)
            score += 800 * level;
        if (lines == 2)
            score += 1200 * level;
        if (lines >= 3)
            score += 1600 * level;
    }

    scoreText.setString(std::to_string(score));
    std::cout << "lines: " << clearedLines << std::endl;
    if (clearedLines >= 10) {
        level++;
        env.setGravity(level);
        levelText.setString(std::to_string(level));
        clearedLines = 0;
    }
}

void Marathon::frameUpdate(sf::Time deltaTime)
{
    (void)deltaTime;
    return;
}

bool Marathon::won()
{
    return false;
}

void Marathon::setRenderPos(sf::Vector2f pos)
{
    background.setPrimitiveType(sf::PrimitiveType::Quads);
    background.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x + 10, pos.y), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x + 10, pos.y + 4), sf::Color(100, 100, 100)));
    background.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 4), sf::Color(100, 100, 100)));
    scoreLabel.setPosition(sf::Vector2f(pos.x + 1, pos.y + 1));
    scoreText.setPosition(sf::Vector2f(pos.x + 3.5, pos.y + 1));
    levelLabel.setPosition(sf::Vector2f(pos.x + 1, pos.y + 2));
    levelText.setPosition(sf::Vector2f(pos.x + 3.5, pos.y + 2));
}

}