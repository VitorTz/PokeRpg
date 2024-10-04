cmake_minimum_required(VERSION 3.29)
project(PokeRpg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(PokeRpg src/main.cpp
        src/pokemon.h
        src/scene/Scene.h
        src/scene/SceneManager.cpp
        src/scene/TitleScreen.cpp
        src/scene/LoadingScreen.cpp
        src/scene/LevelScene.cpp
        src/scene/TestScene1.cpp
        src/util/TexturePool.h
        src/util/util.h
        src/util/util.cpp
        src/util/TexturePool.cpp
        src/ecs/components.h
        src/ecs/Component.h
        src/ecs/Entity.h
        src/ecs/Entity.cpp
        src/ecs/System.h
        src/ecs/ECS.h
        src/ecs/ECS.cpp
        src/util/Camera.h
        src/util/Camera.cpp
        src/ecs/TransformSystem.cpp
        src/ecs/SpriteSystem.cpp
        src/ecs/SpriteAnimationSystem.cpp)


if ("${PLATFORM}" STREQUAL "Web")
    add_custom_command(
            TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/../assets
    )
    #DEPENDS ${PROJECT_NAME}
else()
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    )
    #DEPENDS ${PROJECT_NAME}
endif()

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file assets)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
