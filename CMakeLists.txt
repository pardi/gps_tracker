cmake_minimum_required(VERSION 3.10)

project(mainMiraGPS)

find_package(Boost REQUIRED filesystem system iostreams) 
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source/header files of the main project
set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

set(HEADERS
  ${HEADERS}
)

set(LIB_NAME miragps)

add_library(${LIB_NAME} STATIC
${CMAKE_CURRENT_SOURCE_DIR}/src/mira_gps.cpp
)

include_directories(include
/app/deps/gnuplot-iostream
${Boost_INCLUDE_DIRS})

target_link_libraries(${LIB_NAME} PUBLIC ${Boost_LIBRARIES}) 

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME}) 

# Add GoogleTest
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(test)
