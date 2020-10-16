/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** ActiveTetrimino
*/

#include <iostream>
#include "ActiveTetrimino.hpp"

namespace Tetris {

const char* CantSpawnError::what() const noexcept
{
    return "ActiveTetrimino couldn't spawn in this gameMatrix";
}

ActiveTetrimino::ActiveTetrimino(TetrminoId id, Tetriminos &tetriminosStats, Matrix<unsigned char> &board) : m_matrix(5, 5)
{
    this->id = id;
    reset(id, tetriminosStats);
    if (!isValid(board, sf::Vector2i(0, 0))) {
        throw CantSpawnError();
    }
}

TetrminoId ActiveTetrimino::getCurrentId()
{
    return id;
}


void ActiveTetrimino::reset(TetrminoId id, Tetriminos &tetriminosStats, int stat)
{
    setStat(id, tetriminosStats, stat);
    this->m_pos = sf::Vector2u(3, 15);

    if (id == 1)
        m_pos.x --;
}

void ActiveTetrimino::setStat(TetrminoId id, Tetriminos &tetristats, int stat)
{
    Matrix<unsigned char> defaultStat = tetristats.getStat(id, stat);

    currentStat = stat;
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            this->m_matrix(x, y) = defaultStat(x, y);
        }
    }
}

bool ActiveTetrimino::rotate(Matrix<unsigned char> &board, Tetriminos &tetriStats, int stat)
{
    int oldstat = currentStat;
    int nstat = stat + currentStat;
    WallKick::Table usedTable = WallKick::NORMAL;
    if (this->id == 1)
        usedTable = WallKick::IPIECE;
    while (nstat >= 4)
        nstat -= 4;
    while (nstat < 0)
        nstat += 4;
    setStat(this->id, tetriStats, nstat);
    for (int t = 0; t < 5; t++) {
        sf::Vector2i oldstatTable = wallkicks.getOffset(usedTable, oldstat, t);
        sf::Vector2i nstatTable = wallkicks.getOffset(usedTable, nstat, t);
        sf::Vector2i translation = oldstatTable - nstatTable;
        if (move(board, translation)) {
            return true;
        }
    }
    setStat(this->id, tetriStats, oldstat);
    return false;
}

int ActiveTetrimino::getStat()
{
    return currentStat;
}

bool ActiveTetrimino::isValid(Matrix<unsigned char> &board, sf::Vector2i offset)
{
    for (unsigned int x = 0; x < 5; x++) {
        for (unsigned int y = 0; y < 5; y++) {
            if (this->m_matrix(x, y) != 0) {
                sf::Vector2i cpos(x + this->m_pos.x + offset.x, y + this->m_pos.y + offset.y);
                if (cpos.x < 0 || cpos.x >= 10 || cpos.y < 0 || board(cpos.x, cpos.y) != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool ActiveTetrimino::move(Matrix<unsigned char> &board, sf::Vector2i direction)
{
    if (!isValid(board, direction))
        return false;
    this->m_pos.x += direction.x;
    this->m_pos.y += direction.y;
    return true;
}

bool ActiveTetrimino::fall(Matrix<unsigned char> &board)
{
    return !move(board, sf::Vector2i(0, -1));
}

Matrix<unsigned char> &ActiveTetrimino::getMatrix() {
    return this->m_matrix;
}

sf::Vector2u ActiveTetrimino::getPosition() {
    return this->m_pos;
}

}