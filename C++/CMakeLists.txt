cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -fext-numeric-literals -fPIC")
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

project(digitsClassification)

add_library(digitsClassification_lib readData.cpp ImageData.cpp)

add_executable(digitsClassification_main main.cpp)
target_link_libraries(digitsClassification_main digitsClassification_lib ${OpenCV_LIBS})
