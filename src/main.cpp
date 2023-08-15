#include <miragps/mira_gps.h>

#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>

int main(){
    mira::Journey jrn;
    jrn.load("../mira_route.csv");
    jrn.log();
    jrn.plot();
    std::cout << "Distance in Km: " << jrn.length() << std::endl;
    return 0;
}
