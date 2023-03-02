cmake_minimum_required(VERSION 3.13)
project(shezuka)
enable_testing()

# Project configuration
set(CMAKE_CXX_STANDARD 14)
include_directories(include)

# ===> Libraries <===
## ==> MEMORY <===
set(MEMORY_LIBNAME shezuka_mem)
add_library(${MEMORY_LIBNAME} SHARED
        include/shezuka/memory/ArrayMemory.h src/shezuka/memory/ArrayMemory.cpp)

## ==> NETWORK <==
set(NETWORK_LIBNAME shezuka_net)
add_library(${NETWORK_LIBNAME} SHARED
        include/shezuka/network/Socket.h src/shezuka/network/Socket.cpp
        include/shezuka/network/SocketListener.h src/shezuka/network/SocketListener.cpp
        include/shezuka/network/SocketClient.h src/shezuka/network/SocketClient.cpp
        include/shezuka/network/TcpListener.h src/shezuka/network/TcpListener.cpp
        include/shezuka/network/TcpClient.h src/shezuka/network/TcpClient.cpp)

## ==> Strings <==
set(STRINGS_LIBNAME shezuka_strings)
add_library(${STRINGS_LIBNAME} SHARED
        include/shezuka/strings/explode.h src/shezuka/strings/explode.cpp)

## ==> Time <==
set(TIME_LIBNAME shezuka_time)
add_library(${TIME_LIBNAME} SHARED
        include/shezuka/time/time.h src/shezuka/time/time.cpp)

# Auto tests on build
function(DO_TEST TEST_NAME TEST_CPP TARGET_LIBNAME)
    add_executable(${TEST_NAME} tests/${TEST_CPP})
    target_link_libraries(${TEST_NAME} pthread ${TARGET_LIBNAME})
    add_test(${TEST_NAME} ${TEST_NAME})
endfunction()

# ===> TESTS <===
## ==> Memory tests <==
DO_TEST(ArrayMemory_Sizing shezuka/memory/ExtendMemoryTest.cpp ${MEMORY_LIBNAME})
DO_TEST(Network_TcpSocketConnection shezuka/network/TcpSocketConnectionTest.cpp ${NETWORK_LIBNAME})
DO_TEST(Network_TcpClientReadAndWrite shezuka/network/TcpClientReadAndWriteTest.cpp ${NETWORK_LIBNAME})
DO_TEST(Explode shezuka/explode/ExplodeTest.cpp ${STRINGS_LIBNAME})
DO_TEST(Time shezuka/time/TimeTest.cpp ${TIME_LIBNAME})