#include "Rater.h"
#include "StrangeAttractor.h"
#include "StrangeSearcher.h"

float LowStandards::rate(const StrangeSearcher* ss) {
    return 1.0f;
}

VolumeRater::VolumeRater(float thresshold)
    : thresshold(thresshold) {

}

float VolumeRater::rate(const StrangeSearcher* ss) {
    auto aabb = ss->getAABB();
    if (aabb.isValid() && aabb.volume() > thresshold )
	return 1.0;
    else
	return -1.0;
}
