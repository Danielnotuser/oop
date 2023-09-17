#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <compare>

namespace Lib {
    class Card {
        private:
            int suit;
            int rank;
            void randcard();
            void correct();
        public:
            // constructors
            Card() {randcard();};
            Card(int r, int s) {rank = r; suit = s; correct();};
            // setters
            Card &set(int r, int s) {
                rank = r; suit = s; correct();
                return *this;
            }
            // getters
            int getR() const {return rank;}
            int getS() const {return suit;}


    }
    std::ostream & operator << (std::ostream &, const Card &);
}

#endif