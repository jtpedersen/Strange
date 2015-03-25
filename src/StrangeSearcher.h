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
    void setRater(std::shared_ptr<Rater> rater);
    void find(int maxAttempts = 10);
    
private:
    StrangeAttractor sa;
    AABB aabb;
    std::shared_ptr<Rater> rater;
};

#endif /* !STRANGESEARCHER_H_ */
