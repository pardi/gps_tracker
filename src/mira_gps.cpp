#include <miragps/mira_gps.h>

namespace mira{

std::ostream& operator<<(std::ostream& os, const Waypoint& wp) {
    os << std::setprecision(6) << "lat: " << wp.latitude << " long: " << wp.longitude << " speed: " << wp.speed;
    return os;
}

inline auto toRad(const double value){
    return value * ( M_PI / 180.0);
}

void Journey::load(const std::filesystem::path & path){
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("load(): The file cannot be openned!");
    }

    std::string line;
    auto line_number = 1;

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line);

        if (tokens.size() != DATA_SIZE){
            std::cout << "[WARNING] Line " << line_number << ": missing information, discarded" << std::endl;
        }
        else{

            journey_.push_back(Waypoint{std::stod(tokens[0]), std::stod(tokens[1]), std::stod(tokens[2])});
        }
        ++line_number;
    }
}

std::vector<std::string> Journey::split(std::string str){   
    std::vector<std::string> tokens;     

    size_t pos = 0;

    while ((pos = str.find(",")) != std::string::npos) {
        
        tokens.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }

    return tokens;
}

void Journey::log(const std::filesystem::path & path){

    if (path.empty()){
        for (const auto& wp: journey_){
            std::cout << wp << std::endl;
        }
    }
    else{
        std::ofstream file(path);

        if (!file.is_open()) {
            throw std::runtime_error("log(): The file cannot be openned!");
        }

        for (const auto& wp: journey_){
            file << wp << std::endl;
        }
    }
}

double Journey::length(){
    double length = 0;

    if (journey_.size() > 1){
        for (size_t idx = 1; idx < journey_.size(); ++idx){
            length += haversineDistance(journey_[idx - 1], journey_[idx]);
        }
    }

    return length;
}

double Journey::haversineDistance(const Waypoint& wp1, const Waypoint& wp2) const {

    auto phi1 = toRad(wp1.latitude);
    auto phi2 = toRad(wp2.latitude);

    auto lambda1 = toRad(wp1.longitude);
    auto lambda2 = toRad(wp2.longitude);

    auto a =    std::pow(std::sin((phi1 - phi2) / 2.0), 2) + 
                std::cos(lambda1) * std::cos(lambda2) * std::pow(std::sin((lambda1 - lambda2) / 2.0), 2);

    auto c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}

void Journey::clear(){
    journey_.clear();
}

void Journey::plot(const std::string & path){
    Gnuplot gp;
    // Set the output terminal and file
    gp << "set terminal pngcairo size 800,600 enhanced font 'Verdana,10'\n";
    gp << "set xlabel 'Longitude'\n";
    gp << "set ylabel 'Latitude'\n";

    if (!path.empty()){
        gp << "set output '" + path + "'\n";
    }
    
    // Converting journey to plotting data
    std::vector<std::pair<double, double>> jrn_data;
    
    for (const auto& wp: journey_){
        jrn_data.push_back({wp.latitude, wp.longitude});
    }
    
    gp << "plot '-' with lines title 'GPS path'\n";
    gp.send1d(jrn_data);
}

}