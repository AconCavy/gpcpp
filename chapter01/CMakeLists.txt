project(Chapter01)

add_executable(${PROJECT_NAME}
        Main.cpp
        Game.hpp Game.cpp)

# include external libraries
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(glm CONFIG REQUIRED)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE glm)
endif ()