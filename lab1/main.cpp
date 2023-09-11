#include <iostream>
#include "lib.h"

using namespace SparseMatrix;

int main() {
    Matrix matr;
    try {
        matr = input(); 
        output("Sourced matrix: ", matr); 
        std::cout << "Result: ";
        int *res = res_vect(matr, cmp1, cmp2);
        for (int i = 0; i < matr.row_size; i++) std::cout << res[i];
        erase(matr);
    }
    catch(const std::bad_alloc& ba) { 
        std::cerr << "Not enough memory." << std::endl;
        erase(matr);
        return 1;
    }
    catch(const std::exception& e) { // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        erase(matr);
        return 1;
    }
    return 0;
}