cmake_minimum_required(VERSION 3.13)
project(rvz-convert)
add_library(Options STATIC src/options.cpp)
target_include_directories(Options PUBLIC ${CMAKE_SOURCE_DIR}/src)
add_executable(Main src/main.cpp)
find_program(MAKE NAMES make)

include(ExternalProject)

externalproject_add(Dolphin
    GIT_REPOSITORY https://github.com/dolphin-emu/dolphin.git
    GIT_SUBMODULES
    GIT_TAG 2412
    PREFIX dolphin
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --target dolphin-tool -j8
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

externalproject_add(WIT
    GIT_REPOSITORY https://github.com/Wiimm/wiimms-iso-tools.git
    GIT_SUBMODULES
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE TRUE
    BUILD_COMMAND ${MAKE} -C project
    PREFIX wit
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
)

target_link_libraries(Main Options)