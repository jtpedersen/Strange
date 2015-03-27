#ifndef STRANGESEARCHER_H_
#define STRANGESEARCHER_H_

#include "StrangeAttractor.h"
#include "aabb.h"

#include <memory>
#include <glm/vec3.hpp>


class Rater;

/**
 * \brief Search for interesting StrangeAttractors
 * stores metrics for the current attractor
 */
class StrangeSearcher {

public:
    /// Inject a strategy for determinig if an attractor is accecptable
    void setRater(std::shared_ptr<Rater> rater);
    /// Try random attractors until there is deemed good enough return value indicates success
    bool find(int maxAttempts = 10);
    /// access the AABB for the current attractor
    const AABB& getAABB() const;
    /// return the current SA
    const StrangeAttractor& getSA() const;
private:
    /// Start at p and step through n points and gather metrics
    void measure(const glm::vec3& p, int n = 100000);
    /// Current sa used for 
    StrangeAttractor sa;
    /// The aabb where the sa has its trajectory
    AABB aabb;
    /// The rater used 
    std::shared_ptr<Rater> rater;
};

#endif /* !STRANGESEARCHER_H_ */
