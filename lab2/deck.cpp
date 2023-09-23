#include <iostream>
#include "deck.h"

namespace Lib {
    Deck::Deck(int n)
    {
        size = n;
        deck = new Card[size];
        for (int i = 0; i < n; )
    }
}
