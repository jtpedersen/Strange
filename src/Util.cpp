#include "Util.h"

#include <random>
#include <iostream>

namespace util {

    glm::vec3 randomPoint() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<> box_dist(-0.5, 0.5);
	return glm::vec3(box_dist(gen), box_dist(gen), box_dist(gen));
    }

    bool fuzzycmp(float a, float b, float tolerance) {
	return std::abs(a-b) < tolerance;
    }

    void message(const std::string& msg) {
	std::cout << msg << std::endl;
    }

    void throwIfNotFinite(const glm::vec3& p) {
	auto test = glm::isfinite(p);
	if ( ! (test.x && test.y && test.z) )
	    throw  std::range_error("point is not finite");
    }

};
