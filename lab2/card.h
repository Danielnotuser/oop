#ifndef CARD_H
#define CARD_H

namespace Lib {
    class Card {
        friend class Deck;
        private:
            int suit;
            int rank;
            void randcard();
            void correct();
        public:
            // constructors
            /**
             * @brief Construct a new Card object - random card
             */
            Card() {randcard();};
            /**
             * @brief Construct a new Card object - exact card 
             * @param r rank of card
             * @param s suit of card
             * @throw throw std::invalid_argument("invalid rank") if rank < 2 or > 14
             * @throw throw std::invalid_argument("invalid suit") if suit < 1 or > 4
             */
            Card(int r, int s) {rank = r; suit = s; correct();};
            // setters
            /**
             * @brief sets rank and suit of card
             * 
             * @param r rank of card
             * @param s suit of card
             * @throw throw std::invalid_argument("invalid rank") if rank < 2 or > 14
             * @throw throw std::invalid_argument("invalid suit") if suit < 1 or > 4
             * @return Card& our card
             */
            Card &set(int r, int s) {
                rank = r; suit = s; correct();
                return *this;
            }
            // getters
            int getR() const {return rank;}
            int getS() const {return suit;}
            // overload
            /**
             * @brief copy assignment
             * 
             * @param ob card that is copied
             * @return Card& our card
             */
            Card & operator=(const Card&ob) {rank = ob.rank; suit = ob.suit; return *this;}
            friend std::ostream &operator<<(std::ostream&, const Card&);
            friend std::istream &operator>>(std::istream&, Card&);
            /**
             * @brief universal comparation of cards
             * @return std::partial_ordering::unordered if cards have different suits
             * @return std::partial_ordering::greater if our card greater that parameter
             */
            std::partial_ordering operator<=>(const Card&) const;
            bool operator == (const Card&) const = default;
            
    };
    
}

#endif
