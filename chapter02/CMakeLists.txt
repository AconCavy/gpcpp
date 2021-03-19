add_executable(c02
        main.cpp
        game.cpp game.hpp
        actor.cpp actor.hpp
        component.cpp component.hpp
        spriteComponent.cpp spriteComponent.hpp
        animationSpriteComponent.cpp animationSpriteComponent.hpp
        backgroundSpriteComponent.cpp backgroundSpriteComponent.hpp
        ship.cpp ship.hpp)

# include utils
target_include_directories(c02 PRIVATE ../utils)

# include external libraries
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(c02 PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(c02 PRIVATE SDL2::SDL2_image)