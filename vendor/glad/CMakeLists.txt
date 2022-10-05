cmake_minimum_required(VERSION 3.21.0)
cmake_policy(VERSION 3.21.0)

project(glad VERSION 0.1.0)

add_library(glad STATIC 
    src/glad.c
)

target_include_directories(glad PUBLIC src include)

if(WIN32)
else()
    target_compile_options(glad PRIVATE "-fPIC")
endif()
