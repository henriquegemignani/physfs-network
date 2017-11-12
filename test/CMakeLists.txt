

add_executable(physfs-network-test physfs-network-test.cxx)
target_link_libraries(physfs-network-test PUBLIC physfs-static physfs-network)