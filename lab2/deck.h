#ifndef DECK_H
#define DECK_H

#include "card.h"

namespace Lib {

    class FullDeck {
        friend class Card;
        private:
            void full_deck();
        public:
            Card arr[52];
            FullDeck() {full_deck();}
    };

    class Deck {
        friend class Card;
        friend class FullDeck;
        private:
            Card *deck;
            int size;
            FullDeck fd;
        public:
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
