set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5
    REQUIRED
    COMPONENTS
        Core
        Gui
        Multimedia
        Widgets
)
find_package(Qt5
    OPTIONAL_COMPONENTS
        Gamepad
)

include_directories(../)

set(UI_SRC
    KeyBindingDialog.cpp
    LogWindow.cpp
    MainWindow.cpp
    Settings.cpp
    SettingsDialog.cpp
)

add_library(zlemu_ui
    ${UI_SRC}
)
target_link_libraries(zlemu_ui
    Qt5::Core
    Qt5::Gui
    Qt5::Multimedia
    Qt5::Widgets
    zlemu_core
)
if (Qt5Gamepad_FOUND)
    target_link_libraries(zlemu_ui
        Qt5::Gamepad
    )
endif()
target_compile_definitions(zlemu_ui
    PRIVATE QT_DEPRECATED_WARNINGS
)