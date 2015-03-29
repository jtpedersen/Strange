#ifndef UTIL_H_
#define UTIL_H_

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/gtx/compatibility.hpp> //glm::isfinite
#include <stdexcept>
#include <string>

namespace util {
    /// random points with in unit box centered on 0,0,0
    glm::vec3 randomPoint();
    /// equals for floating points
    bool fuzzycmp(float a, float b, float tolerance = 1e-5);
    /// centralized user output \todo design gui/tui/log system
    void message(const std::string& msg);
    /// nans and inf are not velcome
    void throwIfNotFinite(const glm::vec3& p);
}

#endif /* !UTIL_H_ */
