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
        friend class FullDeck; // ?
        private:
            Card *deck;
            int size;
            FullDeck fd;
            bool cmp(const Card&, const Card&);
        public:
            // contructors
            Deck(int n = 0); // deck with exact number of cards
            Deck(const Deck&);
            // destructors
            ~Deck() { delete [] deck; }
            // getters
            int getS() const {return size;}
            // overload
            Deck & operator=(const Deck&);
            Card &operator[](int ind) const;
            friend std::ostream &operator<<(std::ostream&, const Deck&);
            friend std::istream &operator>>(std::istream&, Deck&);
            Deck &operator>>=(Deck &a, Deck &b);
            Deck operator+(const Deck&) const;
            // other methods
            void add_rand();
            void add(Card);
            void shuffle();
            bool unique() const;
            Deck sub_deck(int) const;
            void del(int);
            void sort();
    };
}

#endif
