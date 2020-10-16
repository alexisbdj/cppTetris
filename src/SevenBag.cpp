/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** SevenBag
*/

#include <cstdlib>
#include "SevenBag.hpp"

namespace Tetris {

SevenBag::SevenBag()
{
    fill();
}

SevenBag::~SevenBag()
{
}

TetrminoId SevenBag::getNext()
{
    if (bag.size() == 0)
        fill();
    TetrminoId id = bag[0];
    bag.erase(bag.begin());
    return id;
}

void SevenBag::fill()
{
    bag.clear();
    for (int i = 1; i <= 7; i++)
        bag.push_back(i);
    randomize();
}

void SevenBag::randomize()
{
    int currentIndex = this->bag.size();
    TetrminoId temp;
    int randIndex;

    while (currentIndex > 0) {
        randIndex = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * currentIndex;
        if (randIndex == currentIndex)
            randIndex--;
        currentIndex--;
        temp = bag[currentIndex];
        bag[currentIndex] = bag[randIndex];
        bag[randIndex] = temp;
    }
}


}