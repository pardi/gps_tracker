#include <gtest/gtest.h>
#include <miragps/mira_gps.h>

using namespace mira;

constexpr double EQ_TOLERANCE = 1e-2;
constexpr double ABS_TOLERANCE = 1e-9;

class MiraGPSJourneyTest: public Journey{

    public:

    MiraGPSJourneyTest(): Journey(){}
    MiraGPSJourneyTest(const std::filesystem::path & path): Journey(path){}

    auto getJourney(){
        return journey_;
    }

    auto splitTest(std::string str){
        return split(str);
    }

    double haversineDistanceTest(const Waypoint& wp1, const Waypoint& wp2){
        return haversineDistance(wp1, wp2);
    }
};


TEST(MiraGPSTest, TestSplitCorrect) {
    MiraGPSJourneyTest jrn;

    auto tokens = jrn.splitTest("0, 1, 2,");

    EXPECT_TRUE(tokens.size() == 3);

    EXPECT_TRUE(std::stod(tokens[0]) == 0);
    EXPECT_TRUE(std::stod(tokens[1]) == 1);
    EXPECT_TRUE(std::stod(tokens[2]) == 2);

}

TEST(MiraGPSTest, TestSplitNotCorrect) {
    MiraGPSJourneyTest jrn;

    auto tokens = jrn.splitTest("0, 1, 2");

    EXPECT_TRUE(tokens.size() != 3);
}

TEST(MiraGPSTest, TestToRad) {

    double rad = mira::toRad(90.0);

    EXPECT_NEAR(rad, M_PI / 2, ABS_TOLERANCE);

}

TEST(MiraGPSTest, TestStandardCnst) {
    MiraGPSJourneyTest jrn;

    EXPECT_TRUE(jrn.getJourney().empty());

}

TEST(MiraGPSTest, TestLoadPathCnst) {
    MiraGPSJourneyTest jrn("../../test/test_gps_route.csv");

    EXPECT_TRUE(jrn.getJourney().size() == 87);

}

TEST(MiraGPSTest, TestLoad) {
    MiraGPSJourneyTest jrn;
    jrn.load("../../test/test_gps_route.csv");
    EXPECT_TRUE(jrn.getJourney().size() == 87);
}

TEST(MiraGPSTest, TestLoadThrow) {
    MiraGPSJourneyTest jrn;
    EXPECT_THROW(jrn.load("not_existing_path"), std::runtime_error);
}

TEST(MiraGPSTest, TestClear) {
    MiraGPSJourneyTest jrn;
    jrn.load("../../test/test_gps_route.csv");
    jrn.clear();
    EXPECT_TRUE(jrn.getJourney().empty());
}

TEST(MiraGPSTest, TestLog) {
    MiraGPSJourneyTest jrn;
    jrn.load("../../test/test_gps_route.csv");
    jrn.log("tmp_file.txt");
    EXPECT_TRUE(std::filesystem::exists("tmp_file.txt"));
}

TEST(MiraGPSTest, TestLength) {
    MiraGPSJourneyTest jrn;
    jrn.load("../../test/test_gps_route.csv");
    
    EXPECT_NEAR(jrn.length(), 1.56551, EQ_TOLERANCE);
}

TEST(MiraGPSTest, TestHaversineDistance) {
    MiraGPSJourneyTest jrn;
    jrn.load("../../test/test_gps_route.csv");

    Waypoint wp1 = {50.0359, 0.054253};
    Waypoint wp2 = {58.3838, 0.030412};

    EXPECT_NEAR( jrn.haversineDistanceTest(wp1, wp2), 928.248, EQ_TOLERANCE);
}


TEST(MiraGPSTest, TestSmooth) {
    MiraGPSJourneyTest jrn;
    jrn.load("../../test/test_gps_route.csv");

    std::vector<Waypoint> jrn_smooth = jrn.smooth(jrn.getJourney());

    EXPECT_NEAR( jrn_smooth[3].longitude, 51.502, EQ_TOLERANCE);
    EXPECT_NEAR( jrn_smooth[3].latitude, -0.0753788, EQ_TOLERANCE);
}


