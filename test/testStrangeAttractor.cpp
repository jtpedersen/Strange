#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "StrangeAttractor.h"


TEST_CASE( "include SA", "[StrangeAttractor]" ) {
    auto sa = StrangeAttractor::random();
    REQUIRE( true);
}


TEST_CASE( "reload SA", "[StrangeAttractor]" ) {
    for(unsigned int i = 0; i < 10; i++ ) {
	auto sa = StrangeAttractor::random();
	sa.save("tmp.sa");
	auto sa2 = StrangeAttractor::load("tmp.sa");
	REQUIRE( sa == sa2);
    }
}

TEST_CASE( "assign SA", "[StrangeAttractor]" ) {
    auto sa = StrangeAttractor::random();
    auto sa2 = sa;
    REQUIRE( sa == sa2);
}
