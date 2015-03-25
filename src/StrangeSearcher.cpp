#include "StrangeSearcher.h"

void StrangeSearcher::setRater(std::shared_ptr<Rater> rater){
    this->rater = rater;
}
void StrangeSearcher::find(int maxAttempts){
    // generate
    int attempts = 0;
    for(unsigned int attempt = 0; attempt < maxAttempts; attempt++) {
	sa = StrangeAttractor::random();
	// warmup();
	// measure();
	auto rate = rater->rate(this);
	if (rate > 0)
	    break;
    }
}
