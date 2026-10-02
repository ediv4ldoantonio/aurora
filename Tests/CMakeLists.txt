add_executable(AuroraTests EngineTests.cpp)
target_link_libraries(AuroraTests PRIVATE Aurora)
target_compile_definitions(AuroraTests PRIVATE
    AURORA_TEST_ASSET_DIR="${CMAKE_SOURCE_DIR}/Sandbox/Assets")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(AuroraTests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME AuroraTests COMMAND AuroraTests)
