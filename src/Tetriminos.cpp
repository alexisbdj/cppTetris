/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Tetriminos
*/

#include <iostream>
#include "Tetriminos.hpp"

namespace Tetris {

const std::string minos_path = "./data/minos";

void Tetriminos::readTetriminos(std::ifstream &file) {
    int id;
    char name;
    int array[4][5][5];
    file.read(&name, sizeof(char));
    file.read((char*) &id, sizeof(int));
    file.read((char*) &array, sizeof(array));
    TetriminoStat stat(array, id);
    this->tetri_stats.insert({id, stat});
}

Tetriminos::Tetriminos() {
    std::ifstream file;
    file.open(minos_path, std::ios::binary);
    for (int i = 0; i < 7; i++)
        this->readTetriminos(file);
}

Matrix<unsigned char> &Tetriminos::getStat(int id, int stat) {
    TetriminoStat &tetriStat = this->tetri_stats.at(id);
    return tetriStat.getStat(stat);
}


TetriminoStat::TetriminoStat(int (*array)[5][5], int id) : stats(
    {
        Matrix<unsigned char>(5, 5),
        Matrix<unsigned char>(5, 5),
        Matrix<unsigned char>(5, 5),
        Matrix<unsigned char>(5, 5),
    })
{
    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                if (array[i][4 - y][x] != 0)
                    this->stats[i](x, y) = id;
                else
                    this->stats[i](x, y) = 0;
            }
        }
    }
    std::cout << "------------------" << std::endl;
    std::cout << "id: " << id << std::endl;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            std::cout << (int)this->stats[1](x, y);
        }
        std::cout << std::endl;
    }
    this->id = id;
}

Matrix<unsigned char> &TetriminoStat::getStat(int stat) {
    if (stat < 0 || stat > 3) {
        std::cerr << "TetriminoStat id: " << this->id << std::endl;
        std::cerr << "\tgot stat = " << stat << std::endl;
        std::cerr << "-----------" << std::endl;
        stat = 0;
    }
    return this->stats[stat];
}

}