project(c03)

add_executable(${PROJECT_NAME}
        main.cpp
        game.cpp game.hpp
        actor.cpp actor.hpp
        component.cpp component.hpp
        spriteComponent.cpp spriteComponent.hpp
        moveComponent.cpp moveComponent.hpp)

# copy assets
#file(COPY assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

# include utils
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/utils)

# include external libraries
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_image)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)