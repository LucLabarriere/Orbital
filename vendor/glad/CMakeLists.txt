
cmake_minimum_required(VERSION 3.16.0)
cmake_policy(VERSION 3.16.0)

project(glad VERSION 0.1.0)

add_library(glad SHARED
    src/gl.c
)

target_include_directories(glad PUBLIC src include)
