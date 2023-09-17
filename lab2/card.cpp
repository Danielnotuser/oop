#include <iostream>
#include <compare>
#include "card.h"

using namespace Lib;

void Card::randcard()
{
    srand(time(NULL));
    int s = rand() % 4 + 1;
    int r = rand() % 13 + 2;
    this->suit = s;
    this->rank = r;
}

void Card::correct()
{
    if (rank < 2 || rank > 14)
        throw std::invalid_argument("invalid rank");
    if (suit < 1 || suit > 4)
        throw std::invalid_argument("invalid suit");
}

std::ostream & operator << (std::ostream & c, const Card & card)
{
    int r = card.getR();
    if (r <= 10)
        c << r;
    else
    {
        switch (r)
        {
            case 11: c << "J";
            case 12: c << "Q";
            case 13: c << "K";
            case 14: c << "A";
        }
    }
    int s = card.getS();
    switch (s)
    {
        case 1: c << "♥"; // hearts
        case 2: c << "♦"; // diamonds
        case 3: c << "♠"; // spades
        case 4: c << "♣"; // clubs
    }
    return c;
    
}