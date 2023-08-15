#ifndef MIRA_GPS_H
#define MIRA_GPS_H

#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <math.h>
#include <gnuplot-iostream.h>


namespace mira{

    // Size of the fields contained in every GPS message 
    // <long, latitude, speed>
    constexpr size_t DATA_SIZE = 3; 

    // Size of the earth in KM
    constexpr double EARTH_RADIUS_KM = 6371.0;

    /**
    * @class Waypoint
    * @brief A simple class to store a waypoints
    *
    * This class provides the minimum set of information to store a waypoint
    */
    struct Waypoint {
        double longitude;
        double latitude;
        double speed;
    };

    /**
    * @class Journey
    * @brief A simple class to store a GPS journey
    *
    * This class provides basic operations for storing, visualising and computing
    * general measurements on a given GPS track given as input
    */
    class Journey{
        public:
            /**
             *@brief Default constructor for the Journey class
            */
            Journey() = default;
            /**
             *@brief Constructor for the Journey class
             *@param path to the file to load containing the gps data
            */
            Journey(const std::filesystem::path & path){
                load(path);
            }
            /**
             *@brief Destructor for the Journey class
            */
            ~Journey() = default;
            /**
             *@brief Function to load the GPS entries in memory
             *@param path to the file to load containing the gps data
            */
            void load(const std::filesystem::path & path);
            /**
             *@brief Function to erase all stored data and release memory
            */
            void clear();
            /**
             *@brief Log to a stream either a file or the Console stream
             *@param path to the file where to store the data, if empty console
             *            is selected
            */
            void log(const std::filesystem::path & path = "");
            /**
             *@brief Length of the total traversed distance by the path contained in the object
            */
            double length();
            /**
             *@brief Plot journey and store it 
             *@param path to the file where to store the new image (.png)
            */
            void plot(const std::string & path = "");  
            /**
             *@brief Plot the path given as input
             *@param journey collection of waypoints to plot
             *@param path to the file where to store the new image (.png)
            */
            void plot(const std::vector<Waypoint> & journey, const std::string & path = "") const;
            /**
             *@brief Plot the original path smoothed using a savizky-golay filter
             *@param path to the file where to store the new image (.png)
            */
            void plotSmooth(const std::string & path = "");

            /**
             *@brief Smooth the path  using a savizky-golay filter
             *@param jrn to smooth
            */
            std::vector<Waypoint> smooth(const std::vector<Waypoint> & jrn);

        protected:
            std::vector<Waypoint> journey_;
            const std::string DELIMITER_{","};

            /**
             *@brief Parse a line of the GPS data file
             *@param str containing a line of the file
            */
            std::vector<std::string> split(std::string str);

            /**
             *@brief Compute the distance over a sphere between two points using long/lat
             *@param wp1 first waypoint
             *@param wp2 second waypoint
            */
            double haversineDistance(const Waypoint& wp1, const Waypoint& wp2) const;

    };

    inline auto toRad(const double value){
    return value * ( M_PI / 180.0);
}
}

#endif //MIRA_GPS_H
