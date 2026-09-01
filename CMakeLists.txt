cmake_minimum_required(VERSION 3.20)

project(Aurora)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(
    CMAKE_CXX_STANDARD
    20
)

add_subdirectory(ThirdParty/glad/cmake)
add_subdirectory(ThirdParty/SDL)

glad_add_library(
    glad_gl_core_33
    STATIC
    API gl:core=3.3
)
    
add_subdirectory(Engine)

add_subdirectory(Sandbox)