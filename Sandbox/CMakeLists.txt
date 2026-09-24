file(GLOB_RECURSE SANDBOX_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)


add_executable(
    Sandbox
    ${SANDBOX_SOURCES}
)

target_include_directories(
    Sandbox
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_link_libraries(
    Sandbox
    PRIVATE
    Aurora
)

target_compile_definitions(Sandbox PRIVATE
    AURORA_SANDBOX_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Assets"
)
    
