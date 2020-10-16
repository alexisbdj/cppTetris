/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Environment
*/

#ifndef TETRIS_PHYSIQUE_HPP_
#define TETRIS_PHYSIQUE_HPP_

#include <queue>
#include "Matrix.hpp"
#include "Tetriminos.hpp"
#include "SevenBag.hpp"
#include "ActiveTetrimino.hpp"
#include "GameMode.hpp"

namespace Tetris {
    enum Action {
        MoveLeft,
        MoveRight,
        HardDrop,
        RotateLeft,
        RotateRight,
        DasLeft,
        DasRight,
        SoftDropOn,
        SoftDropOff,
        Hold,
        Count,
    };

    class Environment {
        public:
            Environment();
            virtual ~Environment();
            void frame(sf::Time deltaTime, GameMode &gamemode);
            bool addToActionQueue(Tetris::Action action);
            TetrminoId &at(int x, int y);
            ActiveTetrimino &getActive();
            const std::vector<TetrminoId> &getNext() const;
            Tetriminos &getTetriStats();
            bool didLost();
            void setGravity(float g);
            TetrminoId getCurrentHold();
            ActiveTetrimino &getGhost();
        private:
            void performAction(Tetris::Action action, GameMode &gamemode);
            void lock(GameMode &gamemode);
            void checklines(GameMode &gamemode);
            bool checkLine(int y);
            void clearLine(int y);
            TetrminoId takeFromNextQueue();
            void hold();
            bool isTspin();
            void updateGhost();

            SevenBag sevenBag;
            Tetriminos tetrstats;
            std::queue<Tetris::Action> action_queue;
            const int gameWidth;
            const int gameHeight;
            Matrix<TetrminoId> gameMatrix;
            ActiveTetrimino currentTetr;
            ActiveTetrimino ghost;

            std::vector<TetrminoId> nextQueue;

            sf::Time timePerFall;
            sf::Time timeLeftToFall;
            float gravityMultiplier;
            float softDropMultiplier;
            bool hasLost;
            float groundcollision;
            TetrminoId currentHold;
            int combo;
            bool didHold;
    };

}

#endif