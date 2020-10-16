/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Graphical
*/

#include <iostream>
#include "Graphical.hpp"
namespace Tetris {

const sf::Color color_tab[8] = {
    sf::Color(100,100,100),
    sf::Color::Cyan,
    sf::Color::Yellow,
    sf::Color::Magenta,
    sf::Color::Green,
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color(255, 165, 0),
};

Graphical::Graphical()
{
    varray.setPrimitiveType(sf::PrimitiveType::Quads);
    view.reset(sf::FloatRect(-4, 20, 30, -20));
    if (!this->blockTexture.loadFromFile("./data/blockTexture.png")) {
        std::cerr << "can't load block textures" << std::endl;
        exit(84);
    }
}

Graphical::~Graphical()
{
}

void Graphical::update(Tetris::Environment &environment)
{
    varray.clear();
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 20; y++) {
            TetrminoId id = environment.at(x, y);
            addQuad(x, y, id);
        }
    }
    drawGhost(environment);
    Matrix<unsigned char> &active = environment.getActive().getMatrix();
    sf::Vector2u activepos = environment.getActive().getPosition();
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            TetrminoId id = active(x, y);
            if (id != 0)
                addQuad(x + activepos.x, y + activepos.y, id);
        }
    }
    drawNextPreview(environment);
    drawHold(environment);
}

void Graphical::drawHold(Tetris::Environment &environment)
{
    drawPieceAt(environment.getCurrentHold(), -4, 15, environment.getTetriStats());
}

void Graphical::drawGhost(Tetris::Environment &environment)
{
    ActiveTetrimino &ghost = environment.getGhost();
    Matrix<unsigned char> &active = ghost.getMatrix();
    sf::Vector2u activepos = ghost.getPosition();

    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            TetrminoId id = active(x, y);
            if (id != 0)
                addQuad(x + activepos.x, y + activepos.y, id + 7);
        }
    }
}

void Graphical::addQuad(int x, int y, Tetris::TetrminoId id)
{
    sf::Vertex vertex;
    bool loweralpha = false;
    if (id > 7) {
        id -= 7;
        loweralpha = true;
    }
    vertex.color = color_tab[id];
    if (loweralpha)
        vertex.color.a = 100;
    vertex.position = sf::Vector2f(x, y);
    vertex.texCoords = sf::Vector2f(0, 0);
    this->varray.append(vertex);
    vertex.position.x += 1;
    vertex.texCoords.x += 256;
    this->varray.append(vertex);
    vertex.position.y += 1;
    vertex.texCoords.y += 256;
    this->varray.append(vertex);
    vertex.position.x -= 1;
    vertex.texCoords.x -= 256;
    this->varray.append(vertex);
}

void Graphical::drawPieceAt(Tetris::TetrminoId id, int px, int py, Tetriminos &tetriStats)
{
    const sf::Vector2i offsets[7] = {
        sf::Vector2i(-1, +1),
        sf::Vector2i(0, -1),
        sf::Vector2i(0, -1),
        sf::Vector2i(0, -1),
        sf::Vector2i(0, -1),
        sf::Vector2i(0, -1),
        sf::Vector2i(0, -1),
    };
    if (id != 0) {
        Matrix<unsigned char> &k = tetriStats.getStat(id, 0);
        for (int x = 0; x < 5; x++)
            for (int y = 0; y < 5; y++)
                if (k(x, y) != 0) {
                    addQuad(px + x + offsets[k(x, y) - 1].x, y + offsets[k(x, y) - 1].y + py, k(x, y));
                }
    }
}

void Graphical::drawNextPreview(Tetris::Environment &environment)
{
    const std::vector<TetrminoId> &next = environment.getNext();
    const float size = 4;
    Tetriminos &tetriStats = environment.getTetriStats();

    for (unsigned int i = 0; i < next.size(); i++) {
        drawPieceAt(next[i], 11, 19 - size - i * size, tetriStats);
    }
}

void Graphical::render(sf::RenderWindow &window)
{
    sf::RenderStates state = sf::RenderStates::Default;
    state.texture = &this->blockTexture;
    window.setView(view);
    window.draw(varray, state);
}

}