# Target name
set(target BabaGUI)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(${target} ${sources})
target_link_libraries(${target}
	PRIVATE
	Baba
	sfml-graphics
	sfml-main
	sfml-system
	sfml-window
)
