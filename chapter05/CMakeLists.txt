project(Chapter05)

add_executable(${PROJECT_NAME}
        Main.cpp
        Game.cpp Game.hpp
        Actor.cpp Actor.hpp
        Component.cpp Component.hpp
        SpriteComponent.cpp SpriteComponent.hpp
        MoveComponent.cpp MoveComponent.hpp
        Asteroid.cpp Asteroid.hpp
        InputComponent.cpp InputComponent.hpp
        Ship.cpp Ship.hpp
        PositionWrapComponent.cpp PositionWrapComponent.hpp
        CollisionComponent.cpp CollisionComponent.hpp
        Laser.cpp Laser.hpp
        VertexArray.cpp VertexArray.hpp
        Shader.cpp Shader.hpp)

# copy assets
file(COPY assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
file(COPY shaders/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders/)

# include utils
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/utils)

# include external libraries
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_image)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GL)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

find_package(glm CONFIG REQUIRED)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE glm)
endif ()