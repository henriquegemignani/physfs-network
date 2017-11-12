#include "physfs.h"
#include "physfs-network.h"

#include <cstdio>


#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

int main(int argc, char** argv) {
#ifdef _WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }
#endif

	if (!PHYSFS_init(argv[0])) {
		std::printf("PHYSFS_init() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 1;
	}

	if (!PHYSFS_registerArchiver(&PHYSFS_Archiver_Network)) {
		std::printf("PHYSFS_registerArchiver() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 2;
	}

	if (!PHYSFSNetwork_mount("localhost", "8000", "/network", 0)) {
		std::printf("PHYSFSNetwork_mount() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 3;
	}

	if (!PHYSFS_deinit()) {
		std::printf("PHYSFS_deinit() failed!\n  reason: %s.\n", PHYSFS_getLastError());
		return 4;
	}

	return 0;
}