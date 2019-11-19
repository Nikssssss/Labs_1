#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Tritset.h"

TEST_CASE("Creating tritset") {
	Tritset set(0);
	REQUIRE(set.Capacity() == 0);
	REQUIRE(set.TritCapacity() == 0);
	
	REQUIRE_THROWS_AS(Tritset(-1), std::invalid_argument);

	Tritset set1(100);
	REQUIRE(set1.Capacity() == 7);
	REQUIRE(set1.TritCapacity() == 100);

	Tritset set2(112);
	REQUIRE(set2.Capacity() >= 7);
}

TEST_CASE("Indexing operator and memory allocation") {
	Tritset set0(100);
	Tritset set1(200);

	long long allocLength0 = set0.Capacity();

	REQUIRE_THROWS_AS(set0[-2], std::invalid_argument);

	set0[0] = True;
	set0[1] = False;
	set1[1] = True;

	REQUIRE(set0[0] == True);
	REQUIRE(set0[1] == False);
	REQUIRE(set0[2] == set1[0]);

	set0[101] = True;
	REQUIRE(set0[101] == True);
	REQUIRE(set0.Capacity() == allocLength0);

	set0[113] = False;
	REQUIRE(set0[113] == False);
	REQUIRE(set0.Capacity() == 8);

	set0[130] = Unknown;
	REQUIRE(set0.Capacity() == 8);
	REQUIRE(set0[130] == Unknown);

	set0[0] = set1[209];
	REQUIRE(set0[0] == Unknown);

	set0[130] = set1[209];
	REQUIRE(set0.Capacity() == 8);
	REQUIRE(set0[130] == Unknown);

	set0[130] = set1[1];
	REQUIRE(set0[130] == True);
	REQUIRE(set0.Capacity() == 9);

	set0[10] = set1[1];
	set0[12] = set1[0];
	REQUIRE(set0[10] == True);
	REQUIRE(set0[12] == Unknown);
}

TEST_CASE("Tritset = Tritset") {
	Tritset a(10);
	Tritset b(16);

	a[0] = True;
	a[2] = False;
	a[16] = True;

	b = a;

	REQUIRE(b[0] == True);
	REQUIRE(b[2] == False);
	REQUIRE(b[16] == True);
}

TEST_CASE("Bit operations") {
	Tritset a(10);
	Tritset b(20);
	Tritset d(5);
	a[0] = False;
	a[1] = True;
	b[0] = True;
	b[1] = False;
	SECTION("Trit with Trit") {
		REQUIRE((a[0] & a[1]) == False);
		REQUIRE((a[0] | b[0]) == True);
		REQUIRE((a[0] & a[3]) == False);
		REQUIRE((a[1] | b[4]) == True);
		REQUIRE((~a[0]) == True);
		REQUIRE((~b[4]) == Unknown);
		REQUIRE((a[0] & False) == False);
		REQUIRE((b[0] | True) == True);
		REQUIRE((~False) == True);
	}
	SECTION("Tritset with Tritset") {
		d = (a & b);
		REQUIRE(d.Capacity() == b.Capacity());
		REQUIRE(d[1] == False);
		REQUIRE(d[20] == Unknown);
		d = (a | b);
		REQUIRE(d[0] == True);
		REQUIRE(d[1] == True);
		d = (~a);
		REQUIRE(d[0] == True);
		REQUIRE(d[1] == False);
		REQUIRE(d[12] == Unknown);
	}
}

TEST_CASE("Convenient Methods") {
	Tritset a(10), b(16);
	SECTION("Capacity") {
		REQUIRE(a.Capacity() == 1);
		REQUIRE(b.Capacity() == 2);
	}
	SECTION("TritCapacity") {
		REQUIRE(a.TritCapacity() == 10);
		REQUIRE(b.TritCapacity() == 16);
	}
	SECTION("Shrink") {
		a[6] = True;
		a.Shrink();
		b.Shrink();
		REQUIRE(a.Capacity() == 1);
		REQUIRE(a.TritCapacity() == 7);
		REQUIRE(b.Capacity() == 0);
		REQUIRE(b.TritCapacity() == 0);
		Tritset e(0);
		e.Shrink();
		REQUIRE(e.Capacity() == 0);
	}
	SECTION("Trit's Cardinality") {
		a[0] = True;
		a[1] = False;
		a[2] = False;
		a[50] = True;
		a[46] = False;
		REQUIRE(a.Cardinality(True) == 2);
		REQUIRE(a.Cardinality(False) == 3);
		REQUIRE(a.Cardinality(Unknown) == 46);
		REQUIRE(b.Cardinality(True) == 0);
	}
	SECTION("All Cardinalities") {
		a[0] = True;
		a[1] = False;
		a[2] = False;
		a[50] = True;
		a[46] = False;
		std::map<Trit, long long> tempMap;
		tempMap = a.Cardinality();
		REQUIRE(tempMap[False] == 3);
		REQUIRE(tempMap[True] == 2);
		REQUIRE(tempMap[Unknown] == 46);
		tempMap = b.Cardinality();
		REQUIRE(tempMap[True] == 0);
		REQUIRE(tempMap[Unknown] == 16);
	}
	SECTION("Trim") {
		b[10] = True;
		b[9] = False;
		b[1] = True;
		b.Trim(9);
		REQUIRE(b[10] == Unknown);
		REQUIRE(b[9] == Unknown);
		REQUIRE(b[1] == True);
		REQUIRE(b.Capacity() == 1);
		Tritset e(0);
		e.Trim(0);
		REQUIRE(e.Capacity() == 0);
		REQUIRE_THROWS_AS(a.Trim(-2), std::invalid_argument);
		REQUIRE_THROWS_AS(b.Trim(17), std::invalid_argument);
	}
	SECTION("Length") {
		a[7] = True;
		REQUIRE(a.Length() == 8);
		REQUIRE(b.Length() == 0);
		Tritset e(0);
		REQUIRE(e.Length() == 0);
	}
}