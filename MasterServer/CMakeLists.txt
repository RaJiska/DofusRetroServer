cmake_minimum_required (VERSION 2.6)
project (MasterService)

### Main Variables
set (BINARY_NAME MasterServer)

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})
SET(LIBRARY_OUTPUT_PATH ${BIN_DIR})

### Sources & Flags
SET (HDRS
	"${INCLUDE_DIR}/MasterServer.hpp"
	"${INCLUDE_DIR}/Client.hpp"
	"${INCLUDE_DIR}/NetworkMessage.hpp"
	"${INCLUDE_DIR}/CommandFlow.hpp"
	"${INCLUDE_DIR}/ICommand.hpp"
	"${INCLUDE_DIR}/ACommand.hpp"
	"${INCLUDE_DIR}/Commands/Version.hpp"
)

SET (SRCS
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/MasterServer.cpp"
	"${SOURCE_DIR}/Client.cpp"
	"${SOURCE_DIR}/NetworkMessage.cpp"
	"${SOURCE_DIR}/CommandFlow.cpp"
	"${SOURCE_DIR}/ACommand.cpp"
	"${SOURCE_DIR}/Commands/Version.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

### Packages
find_package(Boost)

### CFlags for G++ or Clang
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
add_subdirectory(lib/spdlog)

add_executable(${BINARY_NAME} ${HDRS} ${SRCS})
target_link_libraries(${BINARY_NAME} spdlog)

set_target_properties(${BINARY_NAME} PROPERTIES
	CXX_STANDARD 20
)
