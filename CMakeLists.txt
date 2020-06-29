cmake_minimum_required(VERSION 3.10)

project(Bejeweled)

cmake_policy(SET CMP0076 NEW)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL REQUIRED sdl SDL_image SDL_mixer SDL_ttf)

file(GLOB Sources "src/*.cpp")

add_executable(bejeweled ${Sources})

set_property(TARGET bejeweled PROPERTY CXX_STANDARD 17)
set_property(TARGET bejeweled PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET bejeweled PROPERTY CXX_EXTENSIONS OFF)

target_link_libraries(bejeweled ${SDL_LIBRARIES})
target_include_directories(bejeweled PUBLIC ${SDL_INCLUDE_DIRS})
target_compile_options(bejeweled PUBLIC ${SDL_CFLAGS_OTHER})
