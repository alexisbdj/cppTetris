/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Graphical
*/

#ifndef GRAPHICAL_HPP_
#define GRAPHICAL_HPP_

#include <SFML/Graphics.hpp>
#include "Environment.hpp"

namespace Tetris {

class Graphical {
    public:
        Graphical();
        ~Graphical();
        void update(Tetris::Environment &environment);
        void render(sf::RenderWindow &window);
    private:
        void drawGhost(Tetris::Environment &environment);
        void addQuad(int x, int y, Tetris::TetrminoId id);
        void drawNextPreview(Tetris::Environment &environment);
        void drawHold(Tetris::Environment &environment);
        void drawPieceAt(Tetris::TetrminoId id, int x, int y, Tetriminos &tetriStats);
        sf::VertexArray varray;
        sf::View view;
        sf::Texture blockTexture;
};

}

#endif /* !GRAPHICAL_HPP_ */
