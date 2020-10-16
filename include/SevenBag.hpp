/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** SevenBag
*/

#ifndef SEVENBAG_HPP_
#define SEVENBAG_HPP_

#include "ActiveTetrimino.hpp"

namespace Tetris {

    class SevenBag {
        public:
            SevenBag();
            ~SevenBag();

            TetrminoId getNext();
        protected:
        private:
            void fill();
            void randomize();
            std::vector<TetrminoId> bag;
    };

}

#endif /* !SEVENBAG_HPP_ */
