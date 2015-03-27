#include "StrangeGenerator.h"
#include "Util.h"

#include <stdexcept>

StrangeGenerator::StrangeGenerator(const StrangeAttractor& _sa)
    : sa(_sa) {

}

std::vector<glm::vec3> StrangeGenerator::generate(size_t count) const {
    std::vector<glm::vec3> res;
    auto p = startPoint(1337);
    res.emplace_back(sa.step(p));
    while (res.size() < count) {
	// use last point to step from, emplace for locality
	res.emplace_back(sa.step(res.back()));
    }
    return res;
}

glm::vec3 StrangeGenerator::startPoint(size_t luck) const {
    for(size_t i = 0; i < luck; i++) {
	auto p = util::randomPoint();
	try {
	    p = warmup(p);
	} catch (const std::range_error& err ) {
	    util::message("point was not on attractor");
	    continue;
	}
	return p;
    }
    throw std::runtime_error("could not find point on attractor");
}

glm::vec3 StrangeGenerator::warmup(const glm::vec3& p, size_t count) const {
    glm::vec3 it(p);
    for(size_t i = 0; i < count; i++) {
	it = sa.step(it);
	util::throwIfNotFinite(it);
    }
    return it;
}
