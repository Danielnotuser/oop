#ifndef DECK_H
#define DECK_H

#include "card.h"

namespace Lib {
    /**
     * @class FullDeck Class for full deck with 52 unique cards
     */
    class FullDeck {
        private:
            void full_deck();
        public:
            Card arr[52];
            FullDeck() {full_deck();}
    };
    /**
     * @class Deck Class that contains array of cards
     */
    class Deck {
        private:
            Card *deck;
            int size;
            FullDeck fd;
            static bool cmp(const Card&, const Card&);
        public:
            // contructors
            /**
             * @brief Construct a new Deck object with exact number of cards
             * 
             * @param n Number of cards
             * @throw std::invalid_argument if size is out of range (0..52)
             */
            Deck(int n = 0); 
            /**
             * @brief Construct a new Deck object with copying another
             */
            Deck(const Deck&);
            /**
             * @brief Construct a new Deck object with moving from another
             */
            Deck(Deck&&) noexcept;
            // destructors
            ~Deck() { delete [] deck; }
            // getters
            int getS() const {return size;}
            // overload
            Deck & operator=(const Deck&);
            Deck & operator=(Deck&&) noexcept;
            /**
             * @brief Card from deck array by index
             * 
             * @param ind index of deck array
             * @throw std::invalid_argument if index is out of range (0..size-1)
             * @return const Card& immutable card that can not be changed
             */
            const Card &operator[](int ind) const;
            /**
             * @brief Card from deck array by index
             * 
             * @param ind index of deck array
             * @throw std::invalid_argument if index is out of range (0..size-1)
             * @return Card& changeable card 
             */
            Card &operator[](int ind);
            friend std::ostream &operator<<(std::ostream&, const Deck&);
            friend std::istream &operator>>(std::istream&, Deck&);
            /**
             * @brief Overload >>= moves the top card of our deck into deck b
             * 
             * @param b Deck that will have top card of our deck
             * @throw "No cards for shift" if size of our deck equal to 0
             * @return Deck& our deck
             */
            Deck &operator >>=(Deck &b);
            /**
             * @brief Sum of two decks
             * 
             * @return Deck New deck that contains cards of our deck and parameter
             */
            Deck operator+(const Deck&) const;
            // other methods
            /**
             * @brief adds a random card to our deck
             */
            void add_rand();
            /**
             * @brief adds the exact card to our deck
             * @param constCard& new card to our deck
             */
            void add(const Card&);
            /**
             * @brief shuffles randomly our deck
             * 
             */
            void shuffle();
            /**
             * @brief checks if there are equal cards
             * @return true if there are equal cards
             */
            bool unique() const;
            /**
             * @brief generate subdeck that contains cards with exact suit
             * @param s suit (1..4)
             * @throw std::invalid_argument if suit is out of range (1..4)
             * @return Deck new subdeck 
             */
            Deck sub_deck(int s) const;
            /**
             * @brief delete card in deck by index
             * @param ind index in deck array
             * @throw std::invalid_argument if index is out of range
             * @return Deck& our deck
             */
            Deck &del(int ind);
            /**
             * @brief sorts deck array
             * if suits are equal they are compared by rank
             * else they are compared by suit number
             */
            void sort();
    };
}

#endif
