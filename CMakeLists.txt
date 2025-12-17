cmake_minimum_required (VERSION 3.6)
project (DofusRetroServer)

set (BIN_DIR "${PROJECT_SOURCE_DIR}/bin")
SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

add_subdirectory(MasterServer)