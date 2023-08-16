cmake_minimum_required(VERSION 3.10)

project(miraGPS)

find_package(Boost REQUIRED filesystem system iostreams) 
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source/header files of the main project
set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mira_gps.cpp
)

set(HEADERS
  ${HEADERS}
)

include_directories(include
/app/deps/gnuplot-iostream
${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}) 

# Add GoogleTest
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(test)

# add_executable(${PROJECT_NAME}Tests ${TEST_SOURCES} ${LODEPNG_SOURCE})
# target_link_libraries(${PROJECT_NAME}Tests ${GTEST_BOTH_LIBRARIES} )
# target_include_directories(${PROJECT_NAME}Tests PRIVATE ${CMAKE_SOURCE_DIR}/lodepng ${CMAKE_SOURCE_DIR}/src)
# gtest_discover_tests(${PROJECT_NAME}Tests)
