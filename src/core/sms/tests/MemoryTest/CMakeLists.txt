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

add_executable(MemoryTest
    MemoryTest.cpp
    ../../Memory.cpp
    ../../../Logger.cpp
    ../../../Utils.cpp
)

target_link_libraries(MemoryTest
    GTest::gtest_main
    Qt5::Core
)

add_test(NAME MemoryTest COMMAND MemoryTest)
set_property(TEST MemoryTest PROPERTY WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_compile_definitions("TESTING")