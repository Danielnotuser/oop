#include <iostream>
#include <string>
#include <limits>
#include <cstring>
#include "lib.h"

using namespace SparseMatrix;

void SparseMatrix::get_num(int &a, int cmp)
{
    while (true) 
    {
        std::cin >> a;
        if (std::cin.eof()) 
            throw std::runtime_error("Failed to read number: EOF");
        else if (std::cin.bad()) 
            throw std::runtime_error(std::string("Failed to read number: ") + std::strerror(errno));
        else if ((std::cin.fail()) || (cmp > 0 && (a <= 0 || a >= cmp)) || (cmp < 0 && a <= 0))
        { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You are wrong; repeat please!" << std::endl;
        }
        else 
            break;
    }
}

void SparseMatrix::push(Line *oldline, LineItem &a)
{
    if (oldline->size == 0)
    {
        Line *oldline = new Line[1];
        *(oldline->root) = a;
    }
    else
    {
        LineItem *rt = oldline->root;
        while (rt->next)
            rt = rt->next;
        *(rt->next) = a;
    }
    (oldline->size)++;
}

void SparseMatrix::erase(Matrix &matr)
{
    if (matr.size != 0)
    {
        for (int i = 0; i < matr.size; i++)
            delete [] matr.lines[i];
    }
    delete [] matr.lines;
}

void SparseMatrix::output(const char *msg, Matrix &matr)
{
    std::cout << msg << std::endl;
    for (int i = 0; i < matr.size; i++)
    {
        std::cout << "Non-zero line elements of line #" << i << ": ";
        LineItem *rt = matr.lines[i]->root;
        while (rt)
        {
            std::cout << rt->info.num << "(" << rt->info.x << ";" << rt->info.y << ") ";
            rt = rt->next;
        }
        std::cout << std::endl;
    }
}

Matrix SparseMatrix::input()
{
    Matrix matr;
    int i = 0;
    try
    {
        int size;
        std::cout << "Write number of the rows: ";
        get_num(size, -1);
        matr.lines = new Line*[size];
        matr.size = size;
        while (true)
        {
            LineItem a;
            std::cout << "Write number of the matrix: ";
            get_num(a.info.num);
            std::cout << std::endl << "Write coordinates of the number (x): ";
            get_num(a.info.x, matr.size);
            std::cout << std::endl << "Write coordinates of the number (y): ";
            get_num(a.info.y, matr.size);
            a.next = nullptr;
            push(matr.lines[a.info.x], a);
        }
    }
    catch(const std::exception &e)
    {
        if  (e.what() != "Failed to read number: EOF" || i == 0)
        {
            erase(matr);
            throw;
        }
    }
    return matr;
}
