#include "physfs.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const PHYSFS_Archiver PHYSFS_Archiver_Network;
int PHYSFSNetwork_mount(const char *hostname, const char* port,
	const char *mountPoint, int appendToPath);

#ifdef __cplusplus
}
#endif
