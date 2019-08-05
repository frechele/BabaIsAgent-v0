# Target name
set(target Baba)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_library(${target} STATIC ${sources})
target_link_libraries(${target}
	PRIVATE
	effolkronium_random
)
