cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    # 静态链接 MT
    option(VS_LINK_STATIC_MT "static link mt." ON)

    if (VS_LINK_STATIC_MT)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
endif()

project(lowdemo)

add_executable(lowc)
set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)
file(GLOB RES_FILES ${RES_DIR}/*.*)

target_sources(
	lowc
	PRIVATE
	"src/main.cpp"
 "src/lex.h")

file(COPY ${RES_DIR} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CONFIGURATION_TYPES}")
message(STATUS "copy ${RES_FILES}")
