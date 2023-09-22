#include <iostream>
#include <compare>
#include "card.h"

using namespace Lib;

int main()
{
    int r, s;
    std::cout << "Enter rank and suit: ";
    std::cin >> r >> s;
    Card c1(r, s);
    std::cout << "Your card: " << c1 << std::endl;
    Card c2;
    std::cout << "Random card: " << c2 << std::endl;
    return 0;
}
