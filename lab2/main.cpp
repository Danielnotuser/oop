#include <iostream>
#include <compare>
#include "card.h"
#include "deck.h"

using namespace Lib;

int main()
{
    srand(time(NULL));
/*
    int r, s;
    Card c2;
    std::cout << "Random card: " << c2 << std::endl;
    std::cout << "Enter rank (2..14) and suit (1:h, 2:d, 3:s, 4:c): ";
    std::cin >> r >> s;
    Card c1(r, s);
    std::cout << "Your card: " << c1 << std::endl;
    std::cout << "Equal: " << (c1 == c2) << std::endl;
    std::cout << "Lower: " << (c1 < c2) << std::endl;
    std::cout << "Greater: " << (c1 > c2) << std::endl;
*/
	Deck d(5);
	std::cout << d;
    d.add_rand();
    std::cout << "add rand: " << d;
    d.shuffle();
    std::cout << "shuffled: " << d;
    std::cout << "unique? " << d.unique();
    Card c(1, 2);
    d.add(c);
    std::cout << "add " << c << ": " << d;
    return 0;
}
