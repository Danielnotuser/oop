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
	Deck d;
	std::cin >> d;
	std::cout << d << std::endl;
    d.add_rand();
    std::cout << "add rand: " << d << std::endl;
    d.shuffle();
    std::cout << "shuffled: " << d << std::endl;
    std::cout << "unique? " << d.unique() << std::endl;
    Card c(11, 3);
    d.add(c);
    std::cout << "add " << c << ": " << d << std::endl;
    std::cout << "sub deck of hearts: " << d.sub_deck(1) << std::endl;
    std::cout << "delete 3 index: " << d.del(3) << std::endl;
    Deck d1(d);
    std::cout << "deck with copy constr: " << d1 << std::endl;
    Deck d2(std::move(d));
    std::cout << "deck with move constr: " << d2 << std::endl;
    std::cout << "our deck: " << d2 << std::endl;
    Deck d3(13);
    std::cout << "deck 3 = " << d3 << std::endl;
    d2 >>= d3;
    std::cout << "our deck after >>: " << d2 << std::endl;
    std::cout << "deck 3 = " << d3 << std::endl;
    d2.sort();
    std::cout << "sorted our deck: " << d2 << std::endl;
    
    
    return 0;
}
