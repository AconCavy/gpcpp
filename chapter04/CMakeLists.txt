project(Chapter04)

add_executable(${PROJECT_NAME}
        Main.cpp
        Game.cpp Game.hpp
        Actor.cpp Actor.hpp
        Component.cpp Component.hpp
        MoveComponent.cpp MoveComponent.hpp
        SpriteComponent.cpp SpriteComponent.hpp
        AIState.cpp AIState.hpp
        AIComponent.cpp AIComponent.hpp
        NavComponent.cpp NavComponent.hpp
        Tile.cpp Tile.hpp
        Grid.cpp Grid.hpp
        CollisionComponent.cpp CollisionComponent.hpp
        Enemy.cpp Enemy.hpp
        Bullet.cpp Bullet.hpp
        Tower.cpp Tower.hpp)

# copy assets
#file(COPY assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

# include utils
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/utils)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/utils)

# include external libraries
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_image)

find_package(glm CONFIG REQUIRED)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE glm)
endif ()