/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Game
*/

#include "Game.hpp"
#include "Menu.hpp"
#include "Marathon.hpp"
#include "Sprint.hpp"
#include "Ultra.hpp"
#include "WindowHandling.hpp"

namespace Tetris {

Game::Game() : window(sf::VideoMode(1200, 800), "Tetris")
{
    didInitSuccessfully = true;
    if (!font.loadFromFile("./arial.ttf")) {
        didInitSuccessfully = false;
        return;
    }
    view.reset(sf::FloatRect(0, 0, 1200, 800));
}

Game::~Game()
{
}

int Game::run()
{
    if (!didInitSuccessfully)
        return -1;
    Menu::Choice choice;

    while ((choice = getChoice()) != Menu::LEAVE) {
        if (choice == Menu::SPRINT) {
            Sprint gamemode(font);
            startGame(gamemode);
        }
        else if (choice == Menu::MARATHON) {
            Marathon gamemode(font);
            startGame(gamemode);
        }
        else if (choice == Menu::ULTRA) {
            Ultra gamemode(font);
            startGame(gamemode);
        }
        if (!window.isOpen())
            choice = Menu::LEAVE;
    }
    return 0;
}

Menu::Choice Game::getChoice()
{
    Menu menu(window, font);
    return menu.run();
}

void Game::startGame(GameMode &gamemode)
{
    WindowHandling winh(window, gamemode, font);

    winh.run();
}

}