if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	# Protop: run cmake like this: cmake -G "<generator>" -H. -Bbuild
	message(FATAL_ERROR "Prevented in-tree build.")
endif()

cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

project(physfs-network)
set (CMAKE_CXX_STANDARD 11)

if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MP")
endif()

message(STATUS "-----------------------------------------------------")
message(STATUS "Configuring: physfs")
message(STATUS "-----------------------------------------------------")
add_subdirectory("libs/physfs-3.0.1" ${CMAKE_BINARY_DIR}/physfs)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/libs/asio-1.10.8/include)
target_compile_definitions(asio INTERFACE "-DASIO_STANDALONE")

add_subdirectory("client")
add_subdirectory("test")