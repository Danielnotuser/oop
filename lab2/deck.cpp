#include <iostream>
#include <algorithm>
#include <random>
#include "deck.h"

namespace Lib {

	void Deck::full_deck()
	{
		int k = 0;
		for (int i = 2; i < 15; i++)
		{
			for (int j = 1; j < 5; j++)
			{
				(Deck::fd)[k].set(i, j);
			    k++;
			}
		}	
	}
	
    Deck::Deck(int n) : size(n)
    {
        deck = new Card[size];
        std::copy(deck, deck + size, Deck::fd);
        std::shuffle(deck, deck + size, std::random_device());
    }

    std::ostream &operator<<(std::ostream& c, const Deck& d)
    {
    	int n = d.getS();
    	for (int i = 0; i < n; i++)
    	{
    		c << d[i] << " ";
    	}
    	c << std::endl;
    	return c;
    }
}
