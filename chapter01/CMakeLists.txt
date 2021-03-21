project(c01)

add_executable(${PROJECT_NAME}
        main.cpp
        game.hpp game.cpp)

# include external libraries
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
