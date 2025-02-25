cmake_minimum_required(VERSION 3.30)
project(cpp_modules)

set(CMAKE_CXX_STANDARD 20)

include(cmake/copydll.cmake)

add_subdirectory(src)
add_subdirectory(external/SDL)
add_subdirectory(external/entt)