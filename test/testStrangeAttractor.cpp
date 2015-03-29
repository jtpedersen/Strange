#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "StrangeAttractor.h"
#include "aabb.h"
#include "StrangeSearcher.h"
#include "StrangeGenerator.h"
#include "Rater.h"
#include "Util.h"


TEST_CASE( "compare", "[StrangeAttractor]" ) {
    auto sa1 = StrangeAttractor::random();
    auto sa2 = StrangeAttractor::random();
    REQUIRE( sa1 != sa2);
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


TEST_CASE( "aabb has a center", "[aabb]") {
    AABB aabb;
    aabb.grow(glm::vec3(0));
    auto dist = glm::distance(aabb.center(), glm::vec3(0));
    REQUIRE(util::fuzzycmp(dist, 0));
}

TEST_CASE( "aabb has right center", "[aabb]") {
    AABB aabb;
    aabb.grow(glm::vec3(0));
    aabb.grow(glm::vec3(1));
    auto dist = glm::distance(aabb.center(), glm::vec3(.5));
    REQUIRE(util::fuzzycmp(dist, 0));
    
}



TEST_CASE( "starting the search", "[StrangeSearcher]") {
    StrangeSearcher ss;
    auto rater = std::make_shared<LowStandards>();
    ss.setRater(rater);
    ss.find(10);
}

TEST_CASE( "Volumetric search", "[StrangeSearcher]") {
    StrangeSearcher ss;
    auto rater = std::make_shared<VolumeRater>(.1);
    ss.setRater(rater);
    auto rate = rater->rate(&ss);
    REQUIRE( rate < 0.0);
    REQUIRE(ss.find(1000));
}

TEST_CASE( "generate", "[strange generator]") {
    StrangeSearcher ss;
    auto rater = std::make_shared<VolumeRater>(.1);
    ss.setRater(rater);
    ss.find(1000);
    auto sg = StrangeGenerator(ss.getSA());
    auto ls = sg.generate(100);
    REQUIRE( 100 == ls.size());
}


TEST_CASE( "generator Setting a sa", "[strange generator]") {
    auto sg = StrangeGenerator();
    auto sa = StrangeAttractor::random();

    sg.setSA(sa);

    // it is TDD to put it here when deving - yet the case is trivial and what whould in reality tests?
    // and 100% coverage is nice - how ?

}
