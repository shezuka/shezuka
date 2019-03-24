cmake_minimum_required(VERSION 3.13)
project(memory)
enable_testing()

# Project configuration
set(CMAKE_CXX_STANDARD 14)
include_directories(include)

# ===> Libraries <===
## ==> MEMORY <===
set(MEMORY_LIBNAME shezuka-mem)
add_library(${MEMORY_LIBNAME} SHARED
        include/shezuka/memory/ArrayMemory.h src/shezuka/memory/ArrayMemory.cpp)

## ==> NETWORK <==
set(NETWORK_LIBNAME shezuka-net)
add_library(${NETWORK_LIBNAME} SHARED
        include/shezuka/network/Socket.h src/shezuka/network/Socket.cpp include/shezuka/network/SocketListener.h src/shezuka/network/SocketListener.cpp include/shezuka/network/SocketClient.h src/shezuka/network/SocketClient.cpp)

# Auto tests on build
function(DO_TEST TEST_NAME TEST_CPP TARGET_LIBNAME)
    add_executable(${TEST_NAME} tests/${TEST_CPP})
    target_link_libraries(${TEST_NAME} ${TARGET_LIBNAME})
    add_test(${TEST_NAME} ${TEST_NAME})
    add_custom_command(TARGET ${TEST_NAME}
            POST_BUILD
            COMMAND ctest -C $<CONFIGURATION> --output-on-failure)
endfunction()

# ===> TESTS <===
## ==> Memory tests <==
DO_TEST(ArrayMemory_Sizing shezuka/memory/ExtendMemoryTest.cpp ${MEMORY_LIBNAME})