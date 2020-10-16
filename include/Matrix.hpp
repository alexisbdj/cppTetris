/*
** EPITECH PROJECT, 2020
** tetris (Workspace)
** File description:
** Matrix
*/

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>

template <typename T>
class Matrix
{
public:
    Matrix(std::size_t width, std::size_t height) : m_width(width), m_height(height)
    {
        data.resize(width * height);
	}

    T& operator()(unsigned int x, unsigned int y)
    {
        if (x < 0 || x >= m_width || y < 0 || y > m_height) {
            return data[0];
        }
        return data[x + (y * m_width)];
	}
    T& operator[](unsigned int i)
    {
        return data[i];
    }
    size_t get_x() {
        return m_width;
    }
    size_t get_y() {
        return m_height;
    }
private:
    size_t m_width;
    size_t m_height;
    std::vector<T> data;
};

#endif