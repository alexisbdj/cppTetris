/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** ActiveTetrimino
*/

#ifndef ACTIVETETRIMINO_HPP_
#define ACTIVETETRIMINO_HPP_

#include <SFML/Graphics.hpp>
#include <exception>
#include "Tetriminos.hpp"
#include "WallKick.hpp"

namespace Tetris {

    using TetrminoId = uint8_t;

    class CantSpawnError : public std::exception {
        public:
            virtual const char* what() const noexcept;
    };

    class ActiveTetrimino {
    public:
        ActiveTetrimino(TetrminoId id, Tetriminos &tetriminos_stat, Matrix<unsigned char> &board);
        Matrix<unsigned char> &getMatrix();
        sf::Vector2u getPosition();
        bool move(Matrix<unsigned char> &board, sf::Vector2i direction);
        bool fall(Matrix<unsigned char> &board);
        void reset(TetrminoId id, Tetriminos &tetriminos_stat, int stat = 0);
        void setStat(TetrminoId id, Tetriminos &tetristats, int stat);
        bool rotate(Matrix<unsigned char> &board, Tetriminos &tetriStats, int stat);
        bool isValid(Matrix<unsigned char> &board, sf::Vector2i offset);
        TetrminoId getCurrentId();
        int getStat();
    private:
        Matrix<unsigned char> m_matrix;
        TetrminoId id;
        sf::Vector2u m_pos;
        int currentStat;
        WallKick wallkicks;
    };

}

#endif /* !ACTIVETETRIMINO_HPP_ */
