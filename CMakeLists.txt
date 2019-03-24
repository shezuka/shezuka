cmake_minimum_required(VERSION 3.13)
project(memory)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_NAME memory)

include_directories(include)

add_library(${LIBRARY_NAME} SHARED
        include/shezuka/memory/ArrayMemory.h src/shezuka/memory/ArrayMemory.cpp)


# Auto tests on build
function(DO_TEST TEST_NAME TEST_CPP)
    add_executable(${TEST_NAME} tests/${TEST_CPP})
    target_link_libraries(${TEST_NAME} ${LIBRARY_NAME})
    add_test(${TEST_NAME} ${TEST_NAME})
    add_custom_command(TARGET ${TEST_NAME}
            POST_BUILD
            COMMAND ctest -C $<CONFIGURATION> --output-on-failure)
endfunction()

# ===> TESTS <===
## ==> Memory tests <==
DO_TEST(ArrayMemory_Sizing shezuka/memory/ExtendMemoryTest.cpp)