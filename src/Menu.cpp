/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Menu
*/

#include <iostream>
#include "Menu.hpp"

namespace Tetris {

Menu::Menu(sf::RenderWindow &win, sf::Font &f) : window(win), font(f)
{
    sf::Vector2f buttonsBase(200, 300);
    float buttonHeight = 40;
    buttons.push_back(Button(sf::FloatRect(buttonsBase.x, buttonsBase.y, 300, buttonHeight), font, "Sprint"));
    buttons.push_back(Button(sf::FloatRect(buttonsBase.x,
        buttonsBase.y + (buttonHeight + 10) * 1, 300, buttonHeight),
            font, "Marathon"));
    buttons.push_back(Button(sf::FloatRect(buttonsBase.x,
        buttonsBase.y + (buttonHeight + 10) * 2, 300, buttonHeight),
            font, "Ultra"));
    view.reset(sf::FloatRect(0, 0, 1200, 800));
    if (logoTexture.loadFromFile("./data/tetrislogo.png")) {
        logoVarray.setPrimitiveType(sf::PrimitiveType::Quads);
        sf::Vertex vertex(sf::Vector2f(160, 100), sf::Color::White, sf::Vector2f(0, 0));
        logoVarray.append(vertex);
        vertex.texCoords.x += 391;
        vertex.position.x += 391;
        logoVarray.append(vertex);
        vertex.texCoords.y += 128;
        vertex.position.y += 128;
        logoVarray.append(vertex);
        vertex.texCoords.x -= 391;
        vertex.position.x -= 391;
        logoVarray.append(vertex);
    }
}

Menu::~Menu()
{
}

Menu::Choice Menu::run()
{
    sf::Clock clock;
    sf::Time deltaTime;
    choice = UNKNOWN;
    sf::Vector2i mousePos;
    bool clicked;

    if (!window.isOpen())
        choice = LEAVE;
    while (choice == UNKNOWN) {
        clicked = false;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                choice = LEAVE;
            else if (event.type == sf::Event::MouseMoved)
                mousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            else if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                    clicked = true;
        }
        update(mousePos, clicked);
        render();
        deltaTime = clock.restart();
        if (deltaTime.asSeconds() < (1.f / 60))
            sf::sleep(sf::seconds(1.f / 60) - deltaTime);
    }
    return choice;
}

void Menu::update(sf::Vector2i mousePos, bool clicked)
{
    if (!clicked)
        return;
    if (buttons[0].isClicked(mousePos))
        choice = SPRINT;
    if (buttons[1].isClicked(mousePos))
        choice = MARATHON;
    if (buttons[2].isClicked(mousePos))
        choice = ULTRA;
}

void Menu::render()
{
    window.setView(view);
    window.clear();
    sf::RenderStates state = sf::RenderStates::Default;
    state.texture = &logoTexture;
    window.draw(logoVarray, state);
    for (auto it : buttons) {
        it.render(window);
    }
    window.display();
}

}