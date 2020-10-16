
#include <fstream>
#include <map>
#include "Matrix.hpp"

#ifndef TETRIMINOS_HPP_
#define TETRIMINOS_HPP_

namespace Tetris {

class TetriminoStat
{
public:
    TetriminoStat(int (*array)[5][5], int id);
    Matrix<unsigned char> &getStat(int stat);
private:
    Matrix<unsigned char> stats[4];
    int id;
};

class Tetriminos
{
public:
    Tetriminos();
    Matrix<unsigned char> &getStat(int id, int stat);
private:
    void readTetriminos(std::ifstream &file);
    std::map<int, TetriminoStat> tetri_stats;
};

}

#endif