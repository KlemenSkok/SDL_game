cmake_minimum_required(VERSION 3.27.7)
project(test VERSION 0.1.0 LANGUAGES C CXX)


# CMake setup
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})


message(STATUS "")
# SDL2 setup
find_package(SDL2 REQUIRED)
message(STATUS "Found package: ${SDL2_DIR}")

find_package(SDL2_Image REQUIRED)
message(STATUS "Found package: ${SDL2_Image_DIR}")
message(STATUS "")

include_directories(
    ${CMAKE_INCLUDE_PATH}
    "C:/SDL2/SDL2-2.28.0/x86_64-w64-mingw32/include"
    "C:/SDL2_Image/SDL2_image-2.6.2/x86_64-w64-mingw32/include"
)
link_directories(
    "C:/SDL2/SDL2-2.28.0/x86_64-w64-mingw32/lib"
    "C:/SDL2_Image/SDL2_image-2.6.2/x86_64-w64-mingw32/lib"
)

# Files that should be compiled
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.h")

message(STATUS "Add source files:")
foreach(SRC_FILE IN LISTS SRC)
    message(STATUS "${SRC_FILE}")
    endforeach()
    message(STATUS "")
    
add_executable(${PROJECT_NAME} ${SRC})

# LINK PROGRAMS

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    mingw32
    SDL2main
    SDL2
    SDL2_image
)

# Copy over static files

message(STATUS "Copying all dependencies to ${OUTPUT_DIR}")
file(GLOB PROJECT_DEPENDENCIES ${SDL2_LIBRARY})

foreach(Dependecy IN LISTS PROJECT_DEPENDENCIES)
    file(
        COPY ${Dependecy}
        DESTINATION ${OUTPUT_DIR}
    )
endforeach()