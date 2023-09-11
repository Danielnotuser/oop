#ifndef LIB_H
#define LIB_H

namespace SparseMatrix 
{
    typedef struct Item {
        int num;
        int x, y;
    } Item;

    typedef struct LineItem {
        Item info;
        struct LineItem *next;
    } LineItem;

    typedef struct Line {
        LineItem *root;
        int size = 0;
    } Line;

    typedef struct Matrix {
        Line **lines;
        int size = 0;
    } Matrix;

    void get_num(int&, int cmp = 0);
    Matrix input();
    void output(const char*, Matrix&);
    void erase(Matrix&);
    void push(Line*, LineItem&);
}

#endif