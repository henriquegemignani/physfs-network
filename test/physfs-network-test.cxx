#include "physfs.h"
#include "physfs-network.h"

#include <cstdio>

int main(int argc, char** argv) {
	if (!PHYSFS_init(argv[0]))
	{
		std::printf("PHYSFS_init() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 1;
	} /* if */

	PHYSFS_registerArchiver(&PHYSFS_Archiver_Network);

	if (!PHYSFS_deinit())
	{
		std::printf("PHYSFS_deinit() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 1;
	} /* if */

	return 0;
}