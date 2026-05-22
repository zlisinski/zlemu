target_sources(zlemu_core
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Z80.cpp
)

add_subdirectory(tests)