#include "StrangeAttractor.h"
#include "Util.h"

#include <random>
#include <fstream>


StrangeAttractor StrangeAttractor::random() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> coeff_dis(-1.2, 1.2);
    StrangeAttractor res;
    for(auto& c: res.x_coeffs)
	c = coeff_dis(gen);
    for(auto& c: res.y_coeffs)
	c = coeff_dis(gen);
    for(auto& c: res.z_coeffs)
	c = coeff_dis(gen);
    return res;
}

glm::vec3 StrangeAttractor::step(const glm::vec3& p) const {
    glm::vec3 next;
    
    next.x = x_coeffs[0];

    next.x += x_coeffs[1]*p.x;
    next.x += x_coeffs[2]*p.y;
    next.x += x_coeffs[3]*p.z;

    next.x += x_coeffs[4]*p.x*p.x;
    next.x += x_coeffs[5]*p.y*p.y;
    next.x += x_coeffs[6]*p.z*p.z;

    next.x += x_coeffs[7]*p.x*p.y;
    next.x += x_coeffs[8]*p.x*p.z;
    next.x += x_coeffs[9]*p.y*p.z;

    next.y = y_coeffs[0];

    next.y += y_coeffs[1]*p.x;
    next.y += y_coeffs[2]*p.y;
    next.y += y_coeffs[3]*p.z;

    next.y += y_coeffs[4]*p.x*p.x;
    next.y += y_coeffs[5]*p.y*p.y;
    next.y += y_coeffs[6]*p.z*p.z;

    next.y += y_coeffs[7]*p.x*p.y;
    next.y += y_coeffs[8]*p.x*p.z;
    next.y += y_coeffs[9]*p.y*p.z;

    next.z = z_coeffs[0];

    next.z += z_coeffs[1]*p.x;
    next.z += z_coeffs[2]*p.y;
    next.z += z_coeffs[3]*p.z;

    next.z += z_coeffs[4]*p.x*p.x;
    next.z += z_coeffs[5]*p.y*p.y;
    next.z += z_coeffs[6]*p.z*p.z;

    next.z += z_coeffs[7]*p.x*p.y;
    next.z += z_coeffs[8]*p.x*p.z;
    next.z += z_coeffs[9]*p.y*p.z;

    return next;
}


void StrangeAttractor::save(std::string filename) const {
    std::ofstream ofs(filename, std::ios::out | std::ofstream::binary);
    ofs.write(reinterpret_cast<const char *>(x_coeffs.data()), sizeof(float)* x_coeffs.size());
    ofs.write(reinterpret_cast<const char *>(y_coeffs.data()), sizeof(float)* x_coeffs.size());
    ofs.write(reinterpret_cast<const char *>(z_coeffs.data()), sizeof(float)* x_coeffs.size());
}

StrangeAttractor StrangeAttractor::load(std::string filename) {
    StrangeAttractor res;
    std::ifstream ifs(filename, std::ios::binary);

    auto nextFloat = [&ifs] { float f;
			      ifs.read(reinterpret_cast<char*>(&f), sizeof(f));
			      return f;};
    for(auto& c: res.x_coeffs)
    	c = nextFloat();
    for(auto& c: res.y_coeffs)
    	c = nextFloat();
    for(auto& c: res.z_coeffs)
    	c = nextFloat();

    return res;
}


bool StrangeAttractor::operator==(const StrangeAttractor& lhs) const {
    const StrangeAttractor& rhs = *this;
    for(unsigned int i = 0; i < rhs.x_coeffs.size(); i++)
	if (!util::fuzzycmp(rhs.x_coeffs[i], lhs.x_coeffs[i]))
	    return false;
    for(unsigned int i = 0; i < rhs.y_coeffs.size(); i++)
	if (!util::fuzzycmp(rhs.y_coeffs[i], lhs.y_coeffs[i]))
	    return false;
    for(unsigned int i = 0; i < rhs.z_coeffs.size(); i++)
	if (!util::fuzzycmp(rhs.z_coeffs[i], lhs.z_coeffs[i]))
	    return false;
    return true;
}

bool StrangeAttractor::operator!=(const StrangeAttractor& lhs) const {
    return ! (*this == lhs);
}
