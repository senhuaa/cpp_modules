cmake_minimum_required(VERSION 3.30)
project(cpp_modules)

set(CMAKE_CXX_STANDARD 20)

include(cmake/copydll.cmake)

if(MSVC)
    message(STATUS "Using MSVC compiler")

    add_subdirectory(src)
    add_subdirectory(external/SDL)
    add_subdirectory(external/entt)
else()
    message(WARNING "MSVC compiler is required for this project.")
endif()