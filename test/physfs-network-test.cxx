#include "physfs.h"
#include "physfs-network.h"

#include <cstdio>

int main(int argc, char** argv) {
	if (!PHYSFS_init(argv[0])) {
		std::printf("PHYSFS_init() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 1;
	}

	if (!PHYSFS_registerArchiver(&PHYSFS_Archiver_Network)) {
		std::printf("PHYSFS_registerArchiver() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 2;
	}

	if (!PHYSFSNetwork_mount("localhost", 8000, "/network", 0)) {
		std::printf("PHYSFSNetwork_mount() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 3;
	}

	if (!PHYSFS_deinit()) {
		std::printf("PHYSFS_deinit() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 4;
	}

	return 0;
}