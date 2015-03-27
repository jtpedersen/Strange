#ifndef STRANGEGENERATOR_H_
#define STRANGEGENERATOR_H_

#include "StrangeAttractor.h"

#include <vector>
#include <glm/vec3.hpp>

/**
 * \brief A class reposonsible for generating a series of points
 * from a StrangeAttractor
 */
class StrangeGenerator {
public:
    /// Construct a generator with the given sa
    StrangeGenerator(const StrangeAttractor& _sa);
    ///Generate a series of points as vector
    std::vector<glm::vec3> generate(size_t count);
    ///Step the attractor through its trajectory throw if point is out of bounds return point 
    void warmup(size_t count = 1000);
    /// Assuming that sa is an  Attractor find a point on it, using at most luck tries
    const glm::vec3& startPoint(size_t luck = 13);

private:
    /// the sa that this generator creates point from
    const StrangeAttractor sa;
    /// Current possition
    glm::vec3 pos;
};

#endif /* !STRANGEGENERATOR_H_ */
