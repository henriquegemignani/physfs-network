

add_library(physfs-network physfs-network.cxx)
target_link_libraries(physfs-network PUBLIC physfs-static)