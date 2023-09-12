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
        else if ((std::cin.fail()) || (cmp == 0 && a == 0) ||
        	(cmp > 0 && (a < 0 || a >= cmp)) || (cmp < 0 && a <= 0))
        { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You are wrong; repeat please!" << std::endl;
        }
        else 
            break;
    }
}

void SparseMatrix::push(Line* &oldline, LineItem &a)
{
    if (oldline->size == 0)
    {
        oldline->root = new LineItem;
        *(oldline->root) = a;
    }
    else
    {
        LineItem *rt = oldline->root;
        while (rt->next)
            rt = rt->next;
        rt->next = new LineItem;
        *(rt->next) = a;
    }
    (oldline->size)++;
}

void SparseMatrix::erase(Matrix &matr)
{
    if (matr.row_size != 0)
    {
        for (int i = 0; i < matr.row_size; i++)
        {
            if (matr.lines[i])
            {
                LineItem *rt = matr.lines[i]->root;
                LineItem *prev;
                while (rt)
                {
                    prev = rt->next;
                    delete rt;
                    rt = prev;
                }
                delete matr.lines[i];
            }
        }
        delete [] matr.lines;
    }
}

void SparseMatrix::output(const char *msg, Matrix matr)
{
    std::cout << msg << std::endl;
    for (int i = 0; i < matr.row_size; i++)
    {
    	std::cout << "Non-zero line elements of line #" << i << ": ";
        if (matr.lines[i])
        {
	        LineItem *rt = matr.lines[i]->root;
	        while (rt)
	        {
	            std::cout << rt->info.num << "(" << rt->info.x << ";" << rt->info.y << ") ";
	            rt = rt->next;
	        }
	        std::cout << std::endl;
        }
        else
        {
        	std::cout << "Only zero elements." << std::endl;
        }
    }
}

int wrong_coord(int y, Line* row)
{
    if (row->size == 0) return 0;
    LineItem *rt = row->root;
    while (rt)
    {
        if (rt->info.y == y) return 1;
        rt = rt->next;
    }
    return 0;
}

Matrix SparseMatrix::input()
{
    Matrix matr;
    try
    {
        int size;
        std::cout << "Write number of the rows: ";
        get_num(size, -1);
        matr.lines = new Line*[size] {nullptr};//std::fill
        matr.row_size = size;
        std::cout << "Write number of the columns: ";
        get_num(size, -1);
        matr.col_size = size;
        int num;
        std::cout << "Write number of matrix numbers: ";
        get_num(num, -1);
        for (int i = 0; i < num; i++)
        {
	       LineItem a;
	       std::cout << "Write coordinates of the number (x): ";
	       get_num(a.info.x, matr.row_size);
	       if (!matr.lines[a.info.x]) matr.lines[a.info.x] = new Line;
	       do {
	  			std::cout << "Write coordinates of the number (y): ";
	       		get_num(a.info.y, matr.col_size);
	       } while (wrong_coord(a.info.y, matr.lines[a.info.x]));
	       std::cout << "Write number of the line: ";
	       get_num(a.info.num);
	       a.next = nullptr;
	 	   push(matr.lines[a.info.x], a);
 	    }
 	}
 	catch(...)
 	{
 		erase(matr);
 		throw;
 	}
    return matr;
}

bool cmp1(int num)
{
    while (num)
    {
        if (num % 10 == 0) return 0;
        num /= 10;
    }
    return 1;
}

bool cmp2(int num)
{
    int kol = 0;
    while (num)
    {
        if (num % 10 == 1) kol++;
        num /= 10;
    }
    if (kol == 2) return 1;
    return 0;
}

int *SparseMatrix::res_vect(const Matrix &matr, bool (*cmp_s1) (int), bool (*cmp_s2) (int))
{
    int *res = new int[matr.row_size];
    for (int i = 0; i < matr.row_size; i++)
    {
        int s1 = 0, s2 = 0;
        if (matr.lines[i])
        {
        	LineItem* rt = matr.lines[i]->root;
        	while (rt)
        	{
        		if (cmp_s1(rt->info.num))
        			s1 += rt->info.num;
        		if (cmp_s2(rt->info.num))
        		    s2 += rt->info.num;
        		rt = rt->next;
        	}
            res[i] = s1 - s2;	
        }
        else
        {
        	res[i] = 0;
        }
    }
    return res;
}
