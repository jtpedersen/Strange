
#include "StrangeAttractor.h"
#include "StrangeSearcher.h"
#include "StrangeGenerator.h"
#include "Rater.h"

#include <chrono>
#include <iostream>

int main(int argc, char** argv) {

    
    
    StrangeSearcher ss;
    auto rater = std::make_shared<VolumeRater>(.1);
    ss.setRater(rater);
    while (!ss.find(100))
	std::cout << "ping" << std::endl;
    
    std::cout << "********************************************************************************" << std::endl;
    auto sa = ss.getSA();

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    const size_t n = 1000;
    auto g = StrangeGenerator(ss.getSA());
    for(size_t i = 0; i < n ; i++)  {
	auto tmp = g.generate(10000);
	if (tmp.size() < 100)
	    exit(1);
    }

    end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
    
