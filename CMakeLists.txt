cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

project(FSWindow)

file(GLOB SOURCES src/*.cpp)

add_library(FSWindow ${SOURCES})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(FSWindow PRIVATE
        -Wall
        -Wextra
        -Weffc++
        -Wconversion
        -Wsign-conversion
        -Werror
        -pedantic-errors

        $<$<CONFIG:Release>:
            -O3
            -ffast-math
        >
    )
elseif(MSVC)
    target_compile_options(FSWindow PRIVATE
        /fp:fast
        /W4
        /WX
        /permissive-
        $<$<CONFIG:Release>:/O2>
    )
endif()
target_include_directories(FSWindow PUBLIC include)

if(UNIX AND NOT APPLE)
  target_link_libraries(FSWindow X11)
endif()
