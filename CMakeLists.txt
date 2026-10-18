cmake_minimum_required(VERSION 3.15)
project(BSTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ADD_EXECUTABLE TO ADD CPPS
add_executable(BSTree cpp/main.cpp)

if (MSVC)
    target_compile_options(BSTree PRIVATE /W4 /WX)
else()
    target_compile_options(BSTree PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror=return-type
    -Wconversion           
)
endif()
