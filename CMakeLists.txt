cmake_minimum_required(VERSION 3.23)
project(grafika-domaci_1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

add_library(glad src/gl.c)
add_library(shader INTERFACE)
add_library(stb_image src/stb_image.cpp)
add_library(glm INTERFACE)
add_library(sprite src/sprite.cpp)
add_library(game src/game.cpp)
add_library(level1 src/level1.cpp)
add_library(level2 src/level2.cpp)
add_library(level3 src/level3.cpp)
add_library(level4 src/level4.cpp)
add_library(player src/player.cpp)
add_library(framebuffer src/framebuffer.cpp)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(shader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(sprite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(level1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(level2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(level3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(level4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(framebuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE
  PRIVATE
    glad
    glfw
    shader
    stb_image
    glm
    sprite
    game
    player
    framebuffer
    glfw
)

target_link_libraries(sprite PUBLIC stb_image)
target_link_libraries(game PRIVATE glfw level1 level2 level3 level4)
target_link_libraries(level1 PUBLIC sprite player framebuffer)
target_link_libraries(framebuffer PRIVATE glfw)
target_link_libraries(level1 PRIVATE glfw)
target_link_libraries(level2 PRIVATE glfw)
target_link_libraries(level3 PRIVATE glfw)
target_link_libraries(level4 PRIVATE glfw)
target_link_libraries(player PRIVATE glfw)
