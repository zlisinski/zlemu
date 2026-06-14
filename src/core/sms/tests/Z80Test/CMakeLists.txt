include_directories(BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/../CommonMocks
)
include_directories(
    ../../
    ../../../
)

find_package(GTest REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core)

add_executable(Z80Test
    Z80Test.cpp
    ../../Z80.cpp
    ../../../Logger.cpp
    ../../../Utils.cpp
    ../CommonMocks/Bus.cpp
    ../CommonMocks/Memory.cpp
    ../CommonMocks/Timer.cpp
)

target_link_libraries(Z80Test
    GTest::gtest_main
    Qt5::Core
)

add_test(NAME Z80Test COMMAND Z80Test)
set_property(TEST Z80Test PROPERTY WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_compile_definitions("TESTING")