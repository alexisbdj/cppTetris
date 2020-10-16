/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** WindowHandling
*/

#include "WindowHandling.hpp"

namespace Tetris {

WindowHandling::WindowHandling(sf::RenderWindow &win, GameMode &gm, sf::Font &font) : window(win), gamemode(gm)
{
    gamemode.setRenderPos(sf::Vector2f(15, 1));

    mainText.setFont(font);
    howToLeave.setFont(font);

    mainText.setFillColor(sf::Color::White);
    howToLeave.setFillColor(sf::Color::White);

    mainText.setCharacterSize(50);
    howToLeave.setCharacterSize(20);

    mainText.setString("");
    howToLeave.setString("Press Enter to return to main menu");

    mainText.setScale(sf::Vector2f(1.f / 12.f, -1.f / 12.f));
    howToLeave.setScale(sf::Vector2f(1.f / 30.f, -1.f / 30.f));

    mainText.setPosition(sf::Vector2f(1, 10));
    howToLeave.setPosition(sf::Vector2f(0, 5));
}

WindowHandling::~WindowHandling()
{
}

void WindowHandling::handleActions(Tetris::Environment &env, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            env.addToActionQueue(Tetris::Action::MoveLeft);
        }
        else if (event.key.code == sf::Keyboard::Right) {
            env.addToActionQueue(Tetris::Action::MoveRight);
        }
        else if (event.key.code == sf::Keyboard::Down) {
            env.addToActionQueue(Tetris::Action::SoftDropOn);
        }
        else if (event.key.code == sf::Keyboard::Space)
            env.addToActionQueue(Tetris::Action::HardDrop);
        else if (event.key.code == sf::Keyboard::W)
            env.addToActionQueue(Tetris::Action::RotateLeft);
        else if (event.key.code == sf::Keyboard::X)
            env.addToActionQueue(Tetris::Action::RotateRight);
        else if (event.key.code == sf::Keyboard::C)
            env.addToActionQueue(Tetris::Action::Hold);
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Down)
            env.addToActionQueue(Tetris::Action::SoftDropOff);
    }
}

void WindowHandling::run()
{
    sf::Time deltaTime;
    sf::Clock clock;
    isOver = false;
    left = false;

    while (window.isOpen() && !left) {
        deltaTime = clock.restart();
        processEvent();
        update(deltaTime);
        window.clear();
        graph.render(window);
        gamemode.render(window);
        if (isOver) {
            window.draw(mainText);
            window.draw(howToLeave);
        }
        window.display();
    }
}

void WindowHandling::processEvent()
{
    sf::Event event;
    pressedEnter = false;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        handleActions(env, event);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
            pressedEnter = true;
        }
    }
}

void WindowHandling::update(sf::Time deltaTime)
{
    if (!isOver) {
        env.frame(deltaTime, gamemode);
        graph.update(env);

        if (env.didLost()) {
            isOver = true;
            mainText.setString("Lost");
        }
        gamemode.frameUpdate(deltaTime);
        if (gamemode.won()) {
            isOver = true;
            mainText.setString("Won");
        }
    }
    else {
        if (pressedEnter)
            left = true;
    }
}

}