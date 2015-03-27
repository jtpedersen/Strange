#ifndef RATER_H_
#define RATER_H_

class StrangeSearcher;
/**
 * \brief interface to rate the attractiveness of an attractor
 * currently simplicity is king, a rate > 0 =>  pretty
 *
 *
 * And some common strategies used to find rate attractors
 */
class Rater {
public:
    /// return a rate for the current StrangAttractor in the StrangeAttractor
    virtual float rate(const StrangeSearcher* ss) = 0;
};

/// will go for anything
class LowStandards : public Rater {
public:
    virtual float rate(const StrangeSearcher* ss);
};

/// accept based on volume
class VolumeRater : public Rater {
public:
    /// The thresshold for a minimal volume for a trajectory
    VolumeRater(float thresshold);
    virtual float rate(const StrangeSearcher* ss);
private:
    /// minimal acceptable volume
    float thresshold;
};

#endif /* !RATER_H_ */
