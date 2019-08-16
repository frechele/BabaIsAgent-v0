# Target name
set(target pyBaba)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

pybind11_add_module(${target} ${sources})

target_include_directories(${target} 
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Includes
)

set_target_properties(${target}
	PROPERTIES
	${DEFAULT_PROJECT_OPTIONS}
)

target_link_libraries(${target}
	PRIVATE
	Baba
	${DEFAULT_LINKER_OPTIONS}
	spdlog::spdlog
)
