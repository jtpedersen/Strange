#include "StrangeGenerator.h"
#include "Util.h"

#include <stdexcept>

StrangeGenerator::StrangeGenerator() {

}

StrangeGenerator::StrangeGenerator(const StrangeAttractor& _sa)
    : sa(_sa) {
}

void StrangeGenerator::setSA(const StrangeAttractor& sa) {
    this->sa = sa;
}

std::vector<glm::vec3> StrangeGenerator::generate(size_t count) {
    std::vector<glm::vec3> res;
    while (res.size() < count) {
	res.emplace_back(pos);
	pos = sa.step(pos);
    }
    return res;
}

const glm::vec3& StrangeGenerator::startPoint(size_t luck) {
    for(size_t i = 0; i < luck; i++) {
	pos = util::randomPoint();
	try {
	    warmup();
	} catch (const std::range_error& err ) {
	    util::message("point was not on attractor");
	    continue;
	}
	return pos;
    }
    throw std::runtime_error("could not find point on attractor");
}

void StrangeGenerator::warmup(size_t count) {
    for(size_t i = 0; i < count; i++) {
	pos = sa.step(pos);
	util::throwIfNotFinite(pos);
    }
}
