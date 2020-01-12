cmake_minimum_required(VERSION 3.12.4)  # CMake version check
project(crawl_the_dungeon)
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES src/final.cpp src/entities/Soldier.cpp src/enums/TilesEnum.cpp src/Game.cpp src/Game.h src/entities/Character.cpp src/entities/Character.h)

set(SDL2_INCLUDE_DIRS       "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.0.7/include/")
set(SDL2_IMAGE_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2_image-2.0.2/include/")
set(SDL2_TTF_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2_ttf-2.0.14/include/")

set(ARCH "x64")

set(SDL2_LIBPATH "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.0.7/lib/${ARCH}/")
set(SDL2_IMAGE_LIBPATH "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2_image-2.0.2/lib/${ARCH}/")
set(SDL2_TTF_LIBPATH "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2_ttf-2.0.14/lib/${ARCH}/")

if(UNIX)
    find_library(SDL2IMAGE_LIBRARIES SDL2_image PATH ${SDL2_IMAGE_LIBPATH})
    find_library(SDL2_LIB SDL2 PATH ${SDL2_LIBPATH})
    find_library(SDL2_MAIN_LIB SDL2main PATH ${SDL2_LIBPATH})
    find_library(SDL2TTF_LIBRARES SDL2_ttf PATH ${SDL2_TTF_LIBPATH})
else()
    set(SDL2IMAGE_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2_image-2.0.2/lib/x64/SDL2_image.lib")
    set(SDL2_LIB "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.0.7/lib/x64/SDL2.lib")
    set(SDL2_MAIN_LIB "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.0.7/lib/x64/SDL2main.lib")
    set(SDLTTF_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2_image-2.0.14/lib/x64/SDL2_ttf.lib")
    include_directories(SDL2_IMAGE_INCLUDE_DIRS)
    include_directories(SDL2_TTF_INCLUDE_DIRS)
    include_directories(SDL2_INCLUDE_DIRS)
endif()

set(SDL2_LIBRARIES ${SDL2_LIB} ${SDL2_MAIN_LIB} ${SDL2_LIB_LIB})

add_definitions(-DSDL_MAIN_HANDLED)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc")
# Add executable target with source files listed in SOURCE_FILES variable
add_executable(crawl_the_dungeon ${SOURCE_FILES})

set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY MutliThreaded)

if (WIN)
    target_link_options(crawl_the_dungeon PRIVATE -mwindows)
endif ()

target_link_libraries(crawl_the_dungeon
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
        ${SDL2TTF_LIBRARIES}
)
target_include_directories(crawl_the_dungeon SYSTEM PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        )
