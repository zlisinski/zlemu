This is my multisystem emulator project. I'm currently working on Sega Master System. Once that is done, I'll incorporate my existing [Gameboy](https://github.com/zlisinski/zlgb) and [SNES](https://github.com/zlisinski/zlsnes) emulators into this project.

This is a project for me to have fun, so it's not meant to be super accurate or have usability features that I don't care about. It uses Qt for the GUI, so in theory it could build on Windows/Mac, but I only care about running it on Linux with KDE.

The emulator core is built as a library with no dependencies and links with the front-end Qt GUI application. In theory you could have multiple front-ends if for some reason you wanted to use a different GUI framework.

## Requirements

The emulator core has no external requirements other than a version of GCC or Clang with C++20 support and CMake to build it. The unit tests use GoogleTest. The GUI requires Qt and should work on any Qt 5.x version from the last decade.

On Kubuntu 20.04-24.04 you'll need to install the following:

    sudo apt-get install build-essential cmake qtbase5-dev libqt5gamepad5-dev qtmultimedia5-dev libgtest-dev

## Building

Clone the repo and run `make`

## Systems

### Sega Master System / Game Gear
Runs most official games. Video timing isn't exact with regards to which cycles things like interrupts and scroll latching happen.

TODO:
- Save SRAM
- Audio
- Save/Load state
- Game Gear emulation
- Support 3rd party cartridge types with different bank switching
- PAL support
- 224 and 240 line video modes
- SG-1000 video modes
