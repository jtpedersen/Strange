#ifndef AABB_H_
#define AABB_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE 
#include <glm/vec3.hpp>


class AABB {
public:
    AABB();
    void grow(const glm::vec3& p);

    bool isValid() const;
float volume() const;
    
    glm::vec3 low, high;
};

#endif /* !AABB_H_ */
