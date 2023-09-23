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
        	static inline Card fd[52];
        	static void full_deck();
            // contructors
            Deck(int n = 52); // deck with exact number of cards
            // destructors
            ~Deck() { delete [] deck; }
            // getters
            int getS() const {return size;}
            // overload
            Card &operator[](int ind) const {return deck[ind];}
            friend std::ostream &operator<<(std::ostream&, const Deck&);
    };
}

#endif
