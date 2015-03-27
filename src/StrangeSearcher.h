#ifndef STRANGESEARCHER_H_
#define STRANGESEARCHER_H_


#include "StrangeAttractor.h"
#include "aabb.h"

#include <memory>

class StrangeSearcher;


/**
 * \brief interface to rate the attractiveness of an attractor
 * currently simplicity is king, a rate > 0 =>  pretty
 */
class Rater {
public:
    /// return a rate for the current StrangAttractor in the StrangeAttractor
    virtual float rate(const StrangeSearcher* ss) = 0;
};

/// will go for anything
class LowStandards : public Rater {
    virtual float rate(const StrangeSearcher* ss) { return 1.0f; };    
};

/**
 * \brief Search for interesting StrangeAttractors
 * stores metrics for the current attractor
 */
class StrangeSearcher {
    friend class Rater;
public:
    /// Inject a strategy for determinig if an attractor is accecptable
    void setRater(std::shared_ptr<Rater> rater);
    /// Try random attractors until there is deemed good enouhg
    void find(int maxAttempts = 10);
    
private:
    /// Current sa used for 
    StrangeAttractor sa;
    /// The aabb where the sa has its trajectory
    AABB aabb;
    /// The rater used 
    std::shared_ptr<Rater> rater;
};

#endif /* !STRANGESEARCHER_H_ */
