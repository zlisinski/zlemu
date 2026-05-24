cmake_minimum_required(VERSION 3.5.0)
project(zlemu)

#set(CMAKE_C_COMPILER "clang-18")
#set(CMAKE_CXX_COMPILER "clang++-18")
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Winline -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output executables in the current dir, instead of the build dir.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_subdirectory(src)

add_executable(zlemu
    ${MAIN_SRC}
)
target_link_libraries(zlemu
    zlemu_core
    zlemu_ui
)

enable_testing()