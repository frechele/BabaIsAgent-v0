# Target name
set(target BabaGUI)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(${target} ${sources})
target_link_libraries(${target}
	Baba
	sfml-graphics
	sfml-system
	sfml-window
	spdlog::spdlog
)
