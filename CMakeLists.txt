cmake_minimum_required(VERSION 3.12.4)  # CMake version check
SET(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${crawl_the_dungeon_SOURCE_DIR}/CMakePath")

set(TOOLCHAIN_PREFIX i686-w64-mingw32)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(MINGW32_LIBRARY mingw32 "-mwindows" CACHE STRING "link flags for MinGW")

project(crawl_the_dungeon)
set(SOURCE_FILES final.cpp Soldier.cpp TilesEnum.cpp)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(crawl_the_dungeon ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES}
                             ${SDL2_TTF_LIBRARIES}
                             )
