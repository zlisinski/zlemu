include_directories(BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/../CommonMocks
)
include_directories(
    ../../
    ../../../
)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_executable(CpuBenchmark
    CpuBenchmark.cpp
    ../../Z80.cpp
    ../../../Logger.cpp
    ../../../Utils.cpp
    ../CommonMocks/Bus.cpp
    ../CommonMocks/Memory.cpp
    ../CommonMocks/Timer.cpp
)

target_link_libraries(CpuBenchmark
    Qt5::Core
)

add_compile_definitions("TESTING")