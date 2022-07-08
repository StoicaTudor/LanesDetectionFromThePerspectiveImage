# Set minimum CMake version, note
# that CPP23 requires 3.20 minimum
cmake_minimum_required(VERSION 3.20)

# Specify project name with language
project(Work CXX)

# Set CPP standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Set build type if not provided
if(NOT CMAKE_BUILD_TYPE AND NOT (MSVC_IDE OR XCODE))
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type, one of: Release, Debug" FORCE)
endif()

# Disable in-source builds to prevent source tree corruption
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
if(WIN32)
    set(OpenCV_DIR "D:/_Program Files/opencv/build/x64/vc15/lib")
endif()
if(APPLE)
    set(OpenCV_DIR "/usr/local/Cellar/opencv/4.5.1_2/include/opencv4")
endif()
find_package(OpenCV REQUIRED)
# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS " config: ${OpenCV_DIR}")
message(STATUS " version: ${OpenCV_VERSION}")
message(STATUS " libraries: ${OpenCV_LIBS}")
message(STATUS " include path: ${OpenCV_INCLUDE_DIRS}")
file(GLOB srcs *.cpp *.c)
file(GLOB hdrs *.hpp *.h)
include_directories(PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

if (DLIB_NO_GUI_SUPPORT)
    message("No GUI support, so we won't build the ${name} example.")
else()
    add_executable(${PROJECT_NAME} src/main.cpp src/fileutil.cpp src/LaneDetection/LaneDetection.cpp src/LaneDetection/LaneDetection.h)
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
    set (source "${CMAKE_SOURCE_DIR}/assets")
    set (destination "${CMAKE_CURRENT_BINARY_DIR}/assets")
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
            DEPENDS ${destination}
            COMMENT "symbolic link resources folder from ${source} => ${destination}"
    )
endif()