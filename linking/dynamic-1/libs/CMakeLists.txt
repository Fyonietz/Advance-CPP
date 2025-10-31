#libs cmake

file(GLOB_RECURSE LIBRARY "*.cpp")


add_library(libs SHARED ${LIBRARY})

set_target_properties(libs PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_NAME "dynamic"
)

target_link_libraries(libs PRIVATE dl)
