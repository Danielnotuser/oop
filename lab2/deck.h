#ifndef DECK_H
#define DECK_H

#include "card.h"

namespace Lib {
    class Deck {
        friend class Card;
        private:
            Card *deck;
            int size;
        public:
            // contructors
            Deck(int n = 52); // deck with exact number of cards
            // destructors
            ~Deck() { delete [] deck; }
    };
}

#endif