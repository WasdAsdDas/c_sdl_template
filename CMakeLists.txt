cmake_minimum_required(VERSION 3.30)
project(sdl_window C)

set(CMAKE_C_STANDARD 23)

option(SDL_VENDORED "Use vendored libraries" OFF)

if(SDL_VENDORED)
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

add_executable(${PROJECT_NAME} src/main.c)

if(WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

