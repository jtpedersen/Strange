#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "StrangeAttractor.h"
#include "aabb.h"
#include "StrangeSearcher.h"
#include "StrangeGenerator.h"


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

TEST_CASE( "aabb init", "[aabb]") {
    AABB aabb;
    REQUIRE( ! aabb.isValid() );
}

TEST_CASE( "aabb grow one", "[aabb]") {
    AABB aabb;
    aabb.grow(glm::vec3(0));
    REQUIRE( aabb.isValid() );
    REQUIRE( 0 == aabb.volume() );
}

TEST_CASE( "aabb grow more", "[aabb]") {
    AABB aabb;
    aabb.grow(glm::vec3(0));
    aabb.grow(glm::vec3(1.0));
    REQUIRE( 1.0 == aabb.volume() );
}

TEST_CASE( "aabb grow more and do not count it", "[aabb]") {
    AABB aabb;
    aabb.grow(glm::vec3(0));
    aabb.grow(glm::vec3(1.0));

    // "random" selection
    aabb.grow(glm::vec3(.1));
    aabb.grow(glm::vec3(.2));
    aabb.grow(glm::vec3(.72));
    
    REQUIRE( 1.0 == aabb.volume() );
}

TEST_CASE( "startting the search", "[StrangeSearcher]") {
    StrangeSearcher ss;
    auto rater = std::make_shared<LowStandards>();
    ss.setRater(rater);
    ss.find();
}

TEST_CASE( "generate", "[strange generator]") {
    auto sa = StrangeAttractor::random();
    auto sg = StrangeGenerator(sa);

    auto ls = sg.generate(100);
    REQUIRE( 100 == ls.size());
}


