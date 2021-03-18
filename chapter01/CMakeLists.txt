add_executable(c01 main.cpp game.hpp game.cpp)

# include utils
target_include_directories(c01 PRIVATE ../utils)

# include external libraries
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(c01 PRIVATE SDL2::SDL2 SDL2::SDL2main)
