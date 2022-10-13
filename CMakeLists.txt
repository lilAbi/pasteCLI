cmake_minimum_required(VERSION 3.23)
project(pasteCLI)

set(CMAKE_CXX_STANDARD 23)

link_directories("/usr/local/Cellar/llvm/15.0.0/lib/c++")

find_package(CURL)
include_directories(CURL_INCLUDE_DIRS)

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(Boost_INCLUDE_DIRS)
link_directories(${Boost_LIBRARY_DIR})


file(GLOB SRC_FILES CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/core/*.cpp"
        )

add_executable(pasteCLI ${SRC_FILES})

target_link_libraries(pasteCLI ${CURL_LIBRARIES} ${Boost_LIBRARIES})
