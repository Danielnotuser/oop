#include <iostream>
#include "lib.h"
using namespace SparseMatrix;

int main() {
    Matrix matr;
    try {
        matr = input(); 
        output("Sourced matrix", matr); 
//      std::cout << "Result: " << res << std::endl;
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