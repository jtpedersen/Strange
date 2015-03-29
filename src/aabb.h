#ifndef AABB_H_
#define AABB_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE 
#include <glm/vec3.hpp>

/**
 * \brief A basic unoptimized Axis Aligned Bounding Box
 */
class AABB {
public:
    AABB();
    /// Extend to aabb include p
    void grow(const glm::vec3& p);
    /// Is a valid box 
    bool isValid() const;
    /// Volume of the box
    float volume() const;
    /// Return the cneter og the bounding box
    glm::vec3 center() const;

    /// the minimal corner for the aabb
    glm::vec3 low;
    /// the maximal corner for the aabb
    glm::vec3 high;     
};

#endif /* !AABB_H_ */
