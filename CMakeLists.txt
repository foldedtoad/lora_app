# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

set_property(GLOBAL APPEND PROPERTY HEX_FILES_TO_MERGE
      ${app_provision_hex})

set(BOARD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(BOARD nrf52_pca10040_raw)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(lora_app)

target_include_directories(app PRIVATE inc)
target_include_directories(app PRIVATE LoRa_Mac/mac)
target_include_directories(app PRIVATE LoRa_Mac/mac/region)
target_include_directories(app PRIVATE LoRa_Mac/support)

FILE(GLOB app_sources src/*.c)
FILE(GLOB mac_sources LoRa_Mac/mac/*.c)
target_sources(app PRIVATE
  ${app_sources}
  ${mac_sources}
  )

# zephyr_compile_options(-save-temps)
