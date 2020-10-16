/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Ultra
*/

#ifndef ULTRA_HPP_
#define ULTRA_HPP_

#include "GameMode.hpp"

namespace Tetris {

class Ultra : public GameMode {
    public:
        Ultra(sf::Font &font);
        ~Ultra();

        virtual void render(sf::RenderWindow &window);
        virtual void lineCleared(int lines, bool isTspin, int combo, Environment &env);
        virtual void frameUpdate(sf::Time deltaTime);
        virtual bool won();
        virtual void setRenderPos(sf::Vector2f pos);

    private:
        std::string timeToStr(sf::Time time);
        sf::VertexArray background;
        sf::Text scoreLabel;
        sf::Text scoreText;
        sf::Text timer;
        int score;
        sf::Time timeLeft;
        bool timeOver;
};

}

#endif /* !ULTRA_HPP_ */
