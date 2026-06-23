target_sources(zlemu_core
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Bus.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Emulator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Interrupt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vdp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Z80.cpp
)

add_subdirectory(tests)