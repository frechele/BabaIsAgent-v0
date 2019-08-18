# Target name
set(target BabaGUI)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(${target} ${sources})

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)

set_target_properties(${target}
	PROPERTIES
	${DEFAULT_PROJECT_OPTIONS}
)

target_link_libraries(${target}
	PUBLIC
	sfml-graphics
	sfml-system
	sfml-window
	spdlog::spdlog

	PRIVATE
	${DEFAULT_LINKER_OPTIONS}
	Baba
)
