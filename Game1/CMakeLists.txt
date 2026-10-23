# CMakeList.txt : CMake project for Game1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Game1 "Game1.cpp" "Game1.h")
add_subdirectory(raylib)
target_link_libraries(Game1 PRIVATE raylib_static)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game1 PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
