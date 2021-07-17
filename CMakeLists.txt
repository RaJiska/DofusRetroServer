cmake_minimum_required (VERSION 2.6)
project (DofusRetroServer)

### Main Variables
set (BINARY_NAME DofusRetroServer)

set (BIN_DIR "${PROJECT_SOURCE_DIR}/bin")
set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
SET(LIBRARY_OUTPUT_PATH ${BIN_DIR})

### Sources & Flags
SET (HDRS
	"${INCLUDE_DIR}/DofusRetroServer.hpp"
)

SET (SRCS
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/DofusRetroServer.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

# CFlags for G++ or Clang
IF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Winit-self \
		-Wwrite-strings -Wcast-align -Wredundant-decls -Wfloat-equal \
		-Wunreachable-code -Wundef -Wlogical-op -Winline -Wdouble-promotion \
		-Wno-unused-variable -fno-stack-protector"
	)
	IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
	ENDIF()
ENDIF()

### Linking
add_executable(${BINARY_NAME} ${HDRS} ${SRCS})

set_target_properties(${BINARY_NAME} PROPERTIES
	CXX_STANDARD 20
)
