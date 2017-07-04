cmake_minimum_required(VERSION 2.8.3)

project (testAccuracy)
 
# ----------------------- LIBRARIES ---------------------------
find_package(Boost COMPONENTS filesystem system REQUIRED)
find_library(GMP_LIBRARY gmp /usr/lib)


find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# ----------------------- INCLUDES ----------------------------

include_directories(include/)


# ----------------------- GCC FLAGS ----------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")

# ------------------------ BUILD -------------------------------

file(GLOB_RECURSE main_SOURCE )

add_executable(jsonfill src/main.cpp src/OpenMvgJsonHandler.cpp)

target_link_libraries(jsonfill ${GMPXX_LIBRARIES}
                                            ${GMP_LIBRARIES}
                                            ${Boost_LIBRARIES}
                                            ${GMP_LIBRARY}
                                            )
