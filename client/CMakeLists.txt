

add_library(physfs-network src/physfs-network.cxx)
target_link_libraries(physfs-network PUBLIC physfs-static)
target_include_directories(physfs-network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)