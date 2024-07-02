cmake_minimum_required(VERSION 3.16)

project(tools_ut)

include(../../CMakeCommon.cmake)

verifyCppCompiler(8 6)

find_package(Boost 1.58.0 REQUIRED)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(../..)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap,__cxa_throw,--export-dynamic,--no-as-needed")
target_link_libraries(${PROJECT_NAME} ${CMAKE_EXE_LINKER_FLAGS} ${GTEST_BOTH_LIBRARIES} Threads::Threads ncursesw SegFault)
