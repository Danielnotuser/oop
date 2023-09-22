#include <iostream>
#include <compare>
#include "card.h"

namespace Lib {
	void Card::randcard()
	{
	    srand(time(NULL));
	    int s = rand() % 4 + 1; // 1..4
	    int r = rand() % 13 + 2; // 2..14
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
	
	std::ostream &operator <<(std::ostream &c, const Card &card)
	{
	    int r = card.getR();
	    if (r <= 10)
	        c << r;
	    else
	    {
	        switch (r)
	        {
	            case 11: c << "J"; break;
	            case 12: c << "Q"; break;
	            case 13: c << "K"; break;
	            case 14: c << "A"; break;
	        }
	    }
	    int s = card.getS();
	    switch (s)
	    {
	        case 1: c << "♥"; break; // hearts
	        case 2: c << "♦"; break; // diamonds
	        case 3: c << "♠"; break; // spades
	        case 4: c << "♣"; break; // clubs
	    }
	    return c;
	}
	
	std::strong_ordering operator <=>(Card &rc)
	{
		if (suit != rc.suit) 
			throw std::invalid_argument("suits must be equal");
		if (rank < rc.rank)
			return std::strong_ordering::less;
		else if (rank > rc.rank)
			return std::strong_ordering::greater;
		else
			return std::strong_ordering::equal;
	}
}

