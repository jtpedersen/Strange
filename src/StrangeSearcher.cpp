#include "StrangeSearcher.h"
#include "StrangeGenerator.h"
#include "Rater.h"
#include "Util.h"

void StrangeSearcher::setRater(std::shared_ptr<Rater> rater){
    this->rater = rater;
}
bool StrangeSearcher::find(int maxAttempts){
    // generate
    int attempts = 0;
    for(unsigned int attempt = 0; attempt < maxAttempts; attempt++) {
	sa = StrangeAttractor::random();
	aabb = AABB();
	auto sq = StrangeGenerator(sa);
	try {
	    auto p = sq.startPoint();
	    measure(p);
	    auto rate = rater->rate(this);
	    if (rate > 0)
		return true;

	} catch (const std::runtime_error& err) {
	    util::message(err.what());
	}
    }
    return false;
}

void StrangeSearcher::measure(const glm::vec3& p, int n) {
    glm::vec3 it(p);
    for(size_t i = 0; i < n ; i++) {
	aabb.grow(it);
	it = sa.step(it);
	util::throwIfNotFinite(it);
    }
}


const AABB& StrangeSearcher::getAABB() const {
    return aabb;
}
