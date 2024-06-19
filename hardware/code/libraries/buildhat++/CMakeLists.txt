
cmake_minimum_required(VERSION 3.10)

project(BuildHAT++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the root directories as the location for local includes
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# Source files, recursively
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Header files, recursively
file(GLOB_RECURSE HEADERS "src/*.hpp" "include/*.hpp")

# Locate libserial library
find_library(LIBSERIAL_LIBRARY NAMES serial REQUIRED)

# Add library include directories
include_directories(${LIBSERIAL_INCLUDE_DIRS})

# Add library targets
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Export library include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Link libserial
target_link_libraries(${PROJECT_NAME} ${LIBSERIAL_LIBRARY})

# Add example executables
add_executable(calibrate_colors examples/calibrate_colors.cpp)
add_executable(drive_one_second examples/drive_one_second.cpp)
add_executable(drive_and_color examples/drive_and_color_example.cpp)
add_executable(drive_and_distance examples/drive_and_distance_example.cpp)
add_executable(color_test_2 examples/color_test_2.cpp)
add_executable(drive_all_test examples/moving2_src/drive_all_test.cpp)

# Link libraries
target_link_libraries(calibrate_colors ${PROJECT_NAME})
target_link_libraries(drive_one_second ${PROJECT_NAME})
target_link_libraries(drive_and_color ${PROJECT_NAME})
target_link_libraries(drive_and_distance ${PROJECT_NAME})
target_link_libraries(color_test_2 ${PROJECT_NAME})
target_link_libraries(drive_all_test ${PROJECT_NAME})

# Add custom "build all" target
add_custom_target(BUILD_ALL ALL DEPENDS
    drive_one_second
    calibrate_colors
    drive_and_color
    drive_and_distance
    color_test_2
    drive_all_test
)