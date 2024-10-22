cmake_minimum_required(VERSION 3.20)
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


add_executable (${PROJECT_NAME} src/main.cpp
        src/constants.h
        src/util/TexturePool.h
        src/util/TexturePool.cpp
        src/util/util.h
        src/util/util.cpp
        src/scene/Scene.h
        src/util/SceneId.h
        src/scene/SceneManager.cpp
        src/scene/TitleScreen.cpp
        src/scene/WorldScene.cpp
        src/ecs/components.h
        src/util/types.h
        src/util/TypeId.h
        src/ecs/EcsManager.h
        src/ecs/EcsManager.cpp
        src/util/MapId.h
        src/util/player.h
        src/util/Direction.h
        src/util/Action.h
        src/ecs/EntityManager.h
        src/ecs/EntityManager.cpp
        src/ecs/SystemManager.h
        src/ecs/ComponentManager.h
        src/util/Camera.h
        src/util/Camera.cpp
        src/scene/TestScene1.cpp
        src/ecs/SystemTransform.cpp
        src/ecs/SystemSprite.cpp
        src/ecs/SystemSpriteAnimation.cpp
        src/ecs/SystemPlayer.cpp
        src/util/PokeType.h
        src/util/TransitionType.h
        src/ecs/SystemTransition.cpp
        src/scene/FireArenaScene.cpp
        src/scene/PlantArenaScene.cpp
        src/scene/WaterArenaScene.cpp
        src/scene/HospitalScene.cpp
        src/scene/HouseScene.cpp
        src/scene/LoadingScreen.cpp
        src/util/TiledMap.h
        src/util/TiledMap.cpp)

        
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -g>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
    $<$<CONFIG:RelWithDebInfo>:-O2 -g>
    $<$<CONFIG:MinSizeRel>:-Os>
)


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
