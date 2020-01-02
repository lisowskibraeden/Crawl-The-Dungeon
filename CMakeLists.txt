cmake_minimum_required(VERSION 3.12.4)  # CMake version check
project(crawl_the_dungeon)
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES final.cpp Soldier.cpp TilesEnum.cpp)
set(SDL2_LIB_DIR ${SDL2_DIR}/lib)

include_directories(${SDL2_DIR}/include)
add_definitions(-DSDL_MAIN_HANDLED)
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(crawl_the_dungeon ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/libSDL2.dll.a ${SDL2_LIB_DIR}/libSDL2main.a ${SDL2_LIB_DIR}/libSDL2_image.dll.a ${SDL2_LIB_DIR}/libSDL2_image.a ${SDL2_DIR}/bin/libpng16-16.dll -mwindows)
