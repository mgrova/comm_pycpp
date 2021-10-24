cmake_minimum_required(VERSION 3.10)
project(comm_pycpp DESCRIPTION "Comm Py-Cpp"
                   LANGUAGES   CXX C
)

##################################
##    General configuration     ##
##################################
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
   SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif()

if(NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE "Debug")
endif()

if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND
   NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
   MESSAGE(FATAL_ERROR "Only Release and Debug build types are allowed.")
endif()

##################################
##       Create Library         ##
##################################
file(GLOB_RECURSE HDRS "./include/*.h")
file(GLOB_RECURSE SRCS "./src/*.cpp")

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ version selection")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_library(${PROJECT_NAME} SHARED ${HDRS} ${SRCS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

##################################
## Loading 3rd party libraries  ##
##################################
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
if(${Python3_FOUND})
    target_link_libraries(${PROJECT_NAME} PUBLIC Python3::Python)
    target_link_libraries(${PROJECT_NAME} PUBLIC Python3::NumPy)
endif(${Python3_FOUND})

find_package(pybind11 CONFIG REQUIRED)
if(${pybind11_FOUND})
    target_link_libraries(${PROJECT_NAME} PUBLIC pybind11::headers)
    target_link_libraries(${PROJECT_NAME} PUBLIC pybind11::embed)
endif(${pybind11_FOUND})

find_package(OpenCV REQUIRED)
if(${OpenCV_FOUND})
    target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
endif(${OpenCV_FOUND})

##################################
##        Add utils             ##
##################################
add_subdirectory(utils)

