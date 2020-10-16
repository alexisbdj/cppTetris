/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Marathon
*/

#ifndef MARATHON_HPP_
#define MARATHON_HPP_

#include "GameMode.hpp"

namespace Tetris {

class Marathon : public GameMode {
    public:
        Marathon(sf::Font &font);
        ~Marathon();

        virtual void render(sf::RenderWindow &window);
        virtual void lineCleared(int lines, bool isTspin, int combo, Environment &env);
        virtual void frameUpdate(sf::Time deltaTime);
        virtual bool won();
        virtual void setRenderPos(sf::Vector2f pos);

    private:
        sf::VertexArray background;
        sf::Text scoreLabel;
        sf::Text scoreText;
        sf::Text levelLabel;
        sf::Text levelText;
        int score;
        int level;
        int clearedLines;
};

}

#endif /* !MARATHON_HPP_ */
