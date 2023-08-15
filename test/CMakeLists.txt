cmake_minimum_required(VERSION 3.10)


# Define your test sources
set(TEST_SOURCES
    test_mira_gps.cpp
)

# Create the test executable
add_executable(tests ${TEST_SOURCES})

# Link Google Test to the test executable
target_link_libraries(tests PRIVATE gtest gtest_main ${LIB_NAME}  )


# Optionally, you can add this line to automatically discover and register tests
gtest_discover_tests(tests)
