/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Sprint
*/

#ifndef SPRINT_HPP_
#define SPRINT_HPP_

#include "GameMode.hpp"

namespace Tetris {

class Sprint : public GameMode {
    public:
        Sprint(sf::Font &font);
        ~Sprint();

        virtual void render(sf::RenderWindow &window);
        virtual void lineCleared(int lines, bool isTspin, int combo, Environment &env);
        virtual void frameUpdate(sf::Time deltaTime);
        virtual bool won();
        virtual void setRenderPos(sf::Vector2f pos);

    private:
        std::string timeToStr(sf::Time time);
        sf::VertexArray background;
        sf::Text linesLabel;
        sf::Text linesText;
        sf::Text timer;
        int linesLeft;
        sf::Time currentTime;
};

}

#endif /* !SPRINT_HPP_ */
