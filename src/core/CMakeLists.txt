find_package(Threads REQUIRED)

include_directories(
    ./
)

set(CORE_SRC
    Emulator.cpp
    Utils.cpp
)

add_library(zlemu_core
    ${CORE_SRC}
)
target_link_libraries(zlemu_core
    Threads::Threads
)

enable_testing()

add_subdirectory(sms)
