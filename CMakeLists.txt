cmake_minimum_required(VERSION 3.19)
project(obb)

set(CMAKE_CXX_STANDARD 17)

find_program(CLANG_FORMAT_EXECUTABLE
        NAMES clang-format
        DOC "Path to clang-format executable."
        )

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES src/*.cpp include/*.cpp)
file(GLOB HEADER_FILES include/*.h)

if (CLANG_FORMAT_EXECUTABLE)
    set(CLANG_FORMAT_ARGS "${CLANG_FORMAT_EXECUTABLE};-i;-style=Google")
    set(FILES_TO_FORMAT ${SOURCE_FILES} ${HEADER_FILES})
    add_custom_target(${CMAKE_PROJECT_NAME}_format
            COMMAND ${CLANG_FORMAT_ARGS} ${FILES_TO_FORMAT})
else ()
    add_custom_target(${CMAKE_PROJECT_NAME}_format COMMAND "")
endif()

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
add_dependencies(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_format)

target_link_libraries(${CMAKE_PROJECT_NAME})
