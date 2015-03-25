#include "aabb.h"

#include <limits>
#include <algorithm>

AABB::AABB() 
    : low(std::numeric_limits<float>::max()), high(std::numeric_limits<float>::min())
{}

void AABB::grow(const glm::vec3& pos) {
    high.x = std::max(pos.x, high.x);
    high.y = std::max(pos.y, high.y);
    high.z = std::max(pos.z, high.z);
    low.x = std::min(pos.x, low.x);
    low.y = std::min(pos.y, low.y);
    low.z = std::min(pos.z, low.z);
}

bool AABB::isValid() const {
    return 
	high.x >= low.x && 
	high.y >= low.y && 
	high.z >= low.z;
}

float AABB::volume() const {
    return std::abs(
	(high.x - low.x) *
	(high.y - low.y) *
	(high.z - low.z)
	);
}
