#ifndef STRANGEATTRACTOR_H_
#define STRANGEATTRACTOR_H_

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>// glm::vec3

#include <string>
#include <array>

class StrangeAttractor {
public:
    /// just random coefficients
    static StrangeAttractor random();

    /// move point on trajectory
    glm::vec3 step(const glm::vec3& p) const;

    /// save as simple dump of coefficients
    static StrangeAttractor load(std::string filename);
    void save(std::string filename) const;

    bool operator==(const StrangeAttractor& lhs) const;
private:
    std::array<float, 10> x_coeffs;
    std::array<float, 10> y_coeffs;
    std::array<float, 10> z_coeffs;
};



#endif /* !STRANGEATTRACTOR_H_ */
