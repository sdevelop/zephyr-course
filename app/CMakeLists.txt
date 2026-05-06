cmake_minimum_required(VERSION 3.20.0)

# Add explicitly app.overlay file to the build.
# This is required because app already defined esp32c3_042_oled board overlay file.
if (${BOARD} MATCHES "^esp32c3_042_oled")
    message(NOTICE "Building for ${BOARD} board, adding app.overlay via EXTRA_DTC_OVERLAY_FILE")
    set (EXTRA_DTC_OVERLAY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/app.overlay")
endif()

set (ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/drivers/our_driver)

list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
find_package(Zephyr REQUIRED)
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)
