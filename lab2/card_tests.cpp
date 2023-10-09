#define CATCH_CONFIG_CARD
#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>
#include "card.h"

srand(time(NULL));
TEST_CASE("Card Constructors")
{
    SECTION("Initializing Constructors") 
    {
        int r = rand() % 13 + 2;
        int s = rand() % 4 + 1; 
        Card c(r, s);
        REQUIRE(c.getS() == s);
        REQUIRE(c.getR() == r);
    }
    SECTION("Test Exceptions")
    {
        REQUIRE_NOTHROWS(Card(r, s));
        REQUIRE_THROWS(Card(1, 3));
        REQUIRE_THROWS(Card(2, 0));
    }

}

TEST_CASE("Card Setters and Getters")
{
    SECTION("Setters and Getters")
    {
        Card c;
        c.set(2, 3);
        REQUIRE(c.getS() == 3);
        REQUIRE(c.getR() == 2);
    }
    SECTION("Test Exceptions")
    {
        REQUIRE_THROWS(c.set(1, 3));
        REQUIRE_THROWS(c.set(2, 0));
    }
    
}
TEST_CASE("Card Overloads")
{
    SECTION("Compare")
    {
        Card c1(2, 3), c2(4, 3);
        REQUIRE(c1 < c2);
        c2.set(2, 3);
        REQUIRE(c1 == c2);
    }
    SECTION("Output")
    {
        std::stringstream out;
        out >> Card(2, 2);
        REQUIRE(out.str() == "2♦");
    }
}