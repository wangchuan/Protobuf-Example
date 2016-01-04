cmake_minimum_required(VERSION 2.9)

set(TARGET_BUILD_PLATFORM x64)

include_directories(./libs/protobuf/include)

project(proto-test)

file(GLOB SOURCES
    src/*.*
)
add_executable(proto-test ${SOURCES})

target_link_libraries(proto-test 
	debug ${CMAKE_CURRENT_SOURCE_DIR}/libs/protobuf/lib/${TARGET_BUILD_PLATFORM}/debug/*.lib
	optimized ${CMAKE_CURRENT_SOURCE_DIR}/libs/protobuf/lib/${TARGET_BUILD_PLATFORM}/release/*.lib
)