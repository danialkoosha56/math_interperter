cmake_minimum_required(VERSION 3.0)  # Specify the minimum version of CMake required

project(interpreter)  # Name your project

# Create an executable named 'myapp' from the source file 'main.c'
add_executable( ${PROJECT_NAME} main.c)