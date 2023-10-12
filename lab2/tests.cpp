#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>
#include "card.h"
#include "deck.h"

TEST_CASE("Card Constructors")
{
    SECTION("Initializing Constructors") 
    {
        int r = GENERATE(1, random() % 13 + 2);
        int s = GENERATE(1, random() % 4 + 1);
        Lib::Card c(r, s);
        REQUIRE(c.getS() == s);
        REQUIRE(c.getR() == r);
    }
    SECTION("Test Exceptions")
    {
    	int r = GENERATE(1, random() % 13 + 2);
        int s = GENERATE(1, random() % 4 + 1); 
        REQUIRE_NOTHROW(Lib::Card(r, s));
        REQUIRE_THROWS(Lib::Card(1, 3));
        REQUIRE_THROWS(Lib::Card(2, 0));
    }

}

TEST_CASE("Card Setters and Getters")
{
    SECTION("Setters and Getters")
    {
        Lib::Card c;
        c.set(2, 3);
        REQUIRE(c.getS() == 3);
        REQUIRE(c.getR() == 2);
    }
    SECTION("Test Exceptions")
    {
    	Lib::Card c;
        REQUIRE_THROWS(c.set(1, 3));
        REQUIRE_THROWS(c.set(2, 0));
    }
    
}
TEST_CASE("Card Overloads")
{
    SECTION("Compare")
    {
        Lib::Card c1(2, 3), c2(4, 3);
        REQUIRE(c1 < c2);
        c2.set(2, 3);
        REQUIRE(c1 == c2);
    }
    
    SECTION("Assignment")
    {
    	Lib::Card c1, c2;
    	c2 = c1;
    	REQUIRE(c1 == c2);	
    }
    
    SECTION("Output")
    {
        std::stringstream out;
        Lib::Card c(2,2);
        out >> c;
        REQUIRE(out.str() == "2♦");
    }
}

TEST_CASE("Deck Constructors")
{
	SECTION("Initializing Constructors")
	{
		int s = GENERATE(take(1, random() % 53));
		Lib::Deck d(s);
		REQUIRE(d.getS() == s);
	}
	SECTION("Copy Constructors")
	{
		int s1 = GENERATE(take(1, random() % 53));
		Lib::Deck d1(s1), d2(d1);
		REQUIRE(d1.getS() == d2.getS());
	}
	SECTION("Move Constructors")
	{
		int s1 = GENERATE(take(1, random() % 53));
		Lib::Deck d1(s1), d2(std::move(d1));
		REQUIRE(d1.getS() == 0);
		REQUIRE(d2.getS() == s1);
	}
	SECTION("Constructors Exceptions")
	{
		REQUIRE_THROWS(Lib::Deck(53));
	}
}

TEST_CASE("Deck Overload")
{
	SECTION("Copy assignment")
	{
		int s1 = GENERATE(take(1, random() % 53)), s2 = GENERATE(take(1, random() % 53));
		Lib::Deck d1(s1), d2(s2);
		d1 = d2;
		REQUIRE(d1.getS() == d2.getS());
	}
	SECTION("Move assignment")
	{
		int s1 = GENERATE(take(1, random() % 53)), s2 = GENERATE(take(1, random() % 53));
		Lib::Deck d1(s1), d2(s2);
		d2 = std::move(d1);
		REQUIRE(d1.getS() == 0);
		REQUIRE(d2.getS() == s1);
	}
	SECTION("Shift")
	{
		int s1 = GENERATE(take(1, random() % 53 + 1)), s2 = GENERATE(take(1, random() % 53 + 1));
		Lib::Deck d1(s1), d2(s2);
		Lib::Card c(d1[s1 - 1].getR(), d1[s1 - 1].getS());
		d1 >>= d2;
		REQUIRE(d2.getS() == s2 + 1);
		REQUIRE(d1.getS() == s1 - 1);
		REQUIRE(d2[s2] == c);
	}
	SECTION("Addition")
	{
		int s1 = GENERATE(take(1, random() % 53 + 1)), GENERATE(take(1, random() % 53 + 1));
		Lib::Deck d1(s1), d2(s2);
		Lib::Deck d3 = d1 + d2;
		REQUIRE(d3.getS() == s1 + s2);
		REQUIRE(d3[0] == d1[0]);
		REQUIRE(d3[d3.getS() - 1] == d2[s2 - 1]);
	}
}

TEST_CASE("Deck Methods")
{
	SECTION("Add random")
	{
		int s1 = GENERATE(take(1, random() % 53 + 1));
		Lib::Deck d1(s1);
		Lib::Card c(d1[s1 - 1].getR(), d1[s1 - 1].getS());
		d1.add_rand();
		REQUIRE(d1.getS() == s1 + 1);
		REQUIRE(!(d1[s1] == c));
	}
	SECTION("Add")
	{
		int s1 = GENERATE(take(1, random() % 53 + 1));
		Lib::Deck d1(s1);
		Lib::Card c;
		d1.add(c);
		REQUIRE(d1.getS() == s1 + 1);
		REQUIRE(d1[s1] == c);	
	}
	SECTION("Unique")
	{
		int s1 = GENERATE(take(1, random() % 53 + 1));
		Lib::Deck d1(s1);
		if (!d1.unique())
		{
			Lib::Card c(d1[0].getR(), d1[0].getS());
			d1.add(c);
		}
		REQUIRE(d1.unique());
	}
	SECTION("Sub Deck")
	{
		int s1 = GENERATE(take(1, random() % 53 + 1));
		Lib::Deck d1(s1);
		Lib::Deck d2(std::move(d1.sub_deck(1)));
		REQUIRE(d2[0].getS() == 1);
	}
	SECTION("Del")
	{
		int s1 = GENERATE(take(1, random() % 53 + 1));
		Lib::Deck d1(s1);
		Lib::Card c(d1[0].getR(), d1[0].getS());
		d1.del(0);
		REQUIRE(d1.getS() == s1 - 1);
		if (s1) REQUIRE(!(d1[0] == c));
	}
	SECTION("Sort")
	{
		int s1 = GENERATE(take(1, random() % 53 + 1));
		Lib::Deck d1(s1);
		for (int i = 0; i < s1 - 1; i++)
			REQUIRE(d1[i] < d1[i + 1]);
	}
}
