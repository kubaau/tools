###
function(verifyCompiler id version gnu clang)
    if ("${id}" STREQUAL "GNU")
        if (${version} VERSION_LESS ${gnu})
            message(FATAL_ERROR "GCC version must be at least " ${gnu})
        endif()
    elseif ("${id}" STREQUAL "Clang")
        if (${version} VERSION_LESS ${clang})
            message(FATAL_ERROR "Clang version must be at least " ${clang})
        endif()
    else()
        message(WARNING "Unsupported compiler!")
    endif()
endfunction(verifyCompiler)

function(verifyCppCompiler gnu clang)
    verifyCompiler(${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} ${gnu} ${clang})
endfunction(verifyCppCompiler)

function(verifyCCompiler gnu clang)
    verifyCompiler(${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} ${gnu} ${clang})
endfunction(verifyCCompiler)
###
include_directories(..)

aux_source_directory(../src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
###
set(CMAKE_COMMON_FLAGS "-Wall -Wextra -Werror -pedantic -g")

set(CMAKE_CXX_FLAGS "${CMAKE_COMMON_FLAGS} -std=c++2a")

set(C_STANDARD c17)
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" AND ${CMAKE_C_COMPILER_VERSION} VERSION_GREATER_EQUAL 9)
    set(C_STANDARD c2x)
endif()
set(CMAKE_C_FLAGS "${CMAKE_COMMON_FLAGS} -D_POSIX_C_SOURCE=999999 -std=${C_STANDARD}")

set(OpenGL_GL_PREFERENCE GLVND)
###
function(dumpParameters)
    message(STATUS "PROJECT_NAME " ${PROJECT_NAME})
    message(STATUS "SRC_LIST " ${SRC_LIST})
    message(STATUS "CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS})
    message(STATUS "CMAKE_CXX_COMPILER_ID " ${CMAKE_CXX_COMPILER_ID})
    message(STATUS "CMAKE_CXX_COMPILER_VERSION " ${CMAKE_CXX_COMPILER_VERSION})
    message(STATUS "CMAKE_C_FLAGS " ${CMAKE_C_FLAGS})
    message(STATUS "CMAKE_C_COMPILER_ID " ${CMAKE_C_COMPILER_ID})
    message(STATUS "CMAKE_C_COMPILER_VERSION " ${CMAKE_C_COMPILER_VERSION})
endfunction(dumpParameters)
###
