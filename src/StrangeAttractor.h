#ifndef STRANGEATTRACTOR_H_
#define STRANGEATTRACTOR_H_

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>// glm::vec3

#include <string>
#include <array>

/**
 * \brief A StrangeAttractor
 * A random sample can be staticly constructoed a
 * There is a step funciton which is threadsage and could be optimized
 * can save and load
 * \todo extend to more than a quadratic map
 */
class StrangeAttractor {
public:
    /// just random coefficients
    static StrangeAttractor random();

    /// move point on trajectory
    glm::vec3 step(const glm::vec3& p) const;

    /// save as simple dump of coefficients
    static StrangeAttractor load(std::string filename);
    /// load a dump of the coefficents
    void save(std::string filename) const;
    /// equal when all coefficents are equal within epsilon
    bool operator==(const StrangeAttractor& lhs) const;
    /// ! == 
    bool operator!=(const StrangeAttractor& lhs) const;

private:
    /// x_coeffs for qaudratic map
    std::array<float, 10> x_coeffs; 
    /// y_coeffs for qaudratic map
    std::array<float, 10> y_coeffs; 
    /// z_coeffs for qaudratic map
    std::array<float, 10> z_coeffs; 
};



#endif /* !STRANGEATTRACTOR_H_ */
