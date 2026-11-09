cmake_minimum_required(VERSION 3.20)

project(Keytester C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(CURL CONFIG REQUIRED)

add_executable(keytester
        src/main.c
        src/requests.c
        src/input.c
)

target_include_directories(keytester PRIVATE src)

target_compile_options(keytester PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

target_link_libraries(keytester PRIVATE CURL::libcurl)

set_target_properties(keytester PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>"
)