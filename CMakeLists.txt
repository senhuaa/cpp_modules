cmake_minimum_required(VERSION 3.30)
project(cpp_modules)

set(CMAKE_CXX_STANDARD 20)

include(cmake/copydll.cmake)

if(MSVC)
    message(STATUS "Using MSVC compiler")

    add_subdirectory(src)
    add_subdirectory(external/SDL)
    add_subdirectory(external/entt)

    set(SDLIMAGE_VENDORED ON)
    set(SDLIMAGE_AVIF OFF)	# disable formats we don't use to make the build faster and smaller.
    set(SDLIMAGE_BMP OFF)
    set(SDLIMAGE_JPEG OFF)
    set(SDLIMAGE_WEBP OFF)
    add_subdirectory(external/SDL_image)
else()
    message(WARNING "MSVC compiler is required for this project.")
endif()