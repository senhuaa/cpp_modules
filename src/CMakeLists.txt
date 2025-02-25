


file(GLOB MODULES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/*/**.ixx)
file(GLOB SOURCE_CPP ${CMAKE_CURRENT_SOURCE_DIR}/*/**.cpp)
add_executable(cpp_modules main.cpp ${SOURCE_CPP})

target_link_libraries(cpp_modules PRIVATE SDL3::SDL3)

target_sources(cpp_modules PRIVATE
        FILE_SET CXX_MODULES
        FILES ${MODULES_FILE})
copy_dll(cpp_modules)