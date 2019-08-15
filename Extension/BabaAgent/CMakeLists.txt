# Target name
set(target BabaAgent)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cc)


add_library(${target} STATIC ${sources})

target_include_directories(${target} 
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Includes
)

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)

target_link_libraries(${target}
	Baba
	${DEFAULT_LINKER_OPTIONS}
	spdlog::spdlog
)
