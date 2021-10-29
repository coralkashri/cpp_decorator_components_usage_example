cmake_minimum_required(VERSION 3.17.3)
project(cpp_decorator_components_usage_example)
set(OUTPUT_FILE_NAME cpp_decorator_components_usage_example)
set(OUTPUT_TEST_FILE_NAME tests_run)

# External Libraries Configurations
## BOOST
set(BOOST_VERSION 1.71.0)
set(BOOST_REQUIRED_COMPONENTS program_options system thread regex filesystem date_time)

# Set Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread ")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/share/cmake-3.18/Modules/)

# Find Packages
find_package(Threads REQUIRED)
find_package(Boost ${BOOST_VERSION} REQUIRED ${BOOST_REQUIRED_COMPONENTS} REQUIRED)

# Set Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Include Directories
include_directories(src)
include_directories(${Boost_INCLUDE_DIRS})

# Link Directories
link_directories(${Boost_LIBRARY_DIRS})

# Project Files
file(GLOB_RECURSE SOURCE_FILES src/*)

# Set Executable
add_executable(${OUTPUT_FILE_NAME} ${SOURCE_FILES})


####################################################################################################################
####################################################################################################################
########################################## GOOGLE UNIT TESTS #######################################################
####################################################################################################################
####################################################################################################################

# Set Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Find Packages
find_package(GTest CONFIG REQUIRED) # GOOGLE UNIT TESTS

# Prepare Files List
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
message(${SOURCE_FILES})
file(GLOB_RECURSE TEST_SOURCE_FILES tests/*)

# Add Sub-Directory GTest
add_subdirectory(ext_libraries/googletest)

enable_testing()

# Include Directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add Executable
add_executable(${OUTPUT_TEST_FILE_NAME} ${SOURCE_FILES} ${TEST_SOURCE_FILES})


####################################################################################################################
####################################################################################################################
######################################### TARGET LINK LIBRARIES ####################################################
####################################################################################################################
####################################################################################################################

file(GLOB_RECURSE GCC_LINK /home/sherlock/softwares/gcc/gcc-my-test/install/lib64/*.so.6)

target_link_libraries(${OUTPUT_FILE_NAME} ${Boost_LIBRARIES})

target_link_libraries(${OUTPUT_TEST_FILE_NAME} ${Boost_LIBRARIES})
target_link_libraries(${OUTPUT_TEST_FILE_NAME} gtest gtest_main)