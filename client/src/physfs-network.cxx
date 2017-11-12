#include "physfs-network.h"
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif
#include "asio.hpp"
#include <cstdio>

#define BAIL(e, r) do { if (e) PHYSFS_setErrorCode(e); return r; } while (0)
#define BAIL_IF(c, e, r) do { if (c) { if (e) PHYSFS_setErrorCode(e); return r; } } while (0)

namespace {
	const int open_archive_integrity = 137641469136;
    std::exception last_exception;

	struct OpenArchiveParameters {
		int integrity;
		const char* hostname;
        const char* port;
	};

	void *Network_openArchive(PHYSFS_Io *io, const char *name, int forWriting, int *claimed) {
		BAIL_IF(forWriting, PHYSFS_ERR_READ_ONLY, nullptr);
        if (std::strcmp(name, ".physfs-network") == 0) {
            *claimed = 1;
        } else {
            BAIL(PHYSFS_ERR_INVALID_ARGUMENT, nullptr);
        }

        OpenArchiveParameters* parameters = (OpenArchiveParameters*) io->opaque;
        BAIL_IF(parameters->integrity != open_archive_integrity, PHYSFS_ERR_INVALID_ARGUMENT, nullptr);

        try {
            asio::io_service io_service;

            asio::ip::tcp::socket s(io_service);
            asio::ip::tcp::resolver resolver(io_service);
            asio::connect(s, resolver.resolve({ parameters->hostname, parameters->port }));

            s.close();
        
        } catch (std::exception& e) {
            last_exception = e;
            BAIL(PHYSFS_ERR_NOT_A_FILE, nullptr);
        }

		BAIL(PHYSFS_ERR_UNSUPPORTED, nullptr);
	}

	PHYSFS_EnumerateCallbackResult Network_dirTreeEnumerate(void *opaque,
		const char *dname, PHYSFS_EnumerateCallback cb,
		const char *origdir, void *callbackdata) {

		return PHYSFS_ENUM_OK;
	}

	PHYSFS_Io *Network_openRead(void *opaque, const char *path)	{
		BAIL(PHYSFS_ERR_NOT_A_FILE, nullptr);
	}

	PHYSFS_Io *Network_openWrite(void *opaque, const char *filename) {
		BAIL(PHYSFS_ERR_READ_ONLY, nullptr);
	}

	PHYSFS_Io *Network_openAppend(void *opaque, const char *filename) {
		BAIL(PHYSFS_ERR_READ_ONLY, nullptr);
	}

	int Network_remove(void *opaque, const char *name) {
		BAIL(PHYSFS_ERR_READ_ONLY, 0);
	}

	int Network_mkdir(void *opaque, const char *name) {
		BAIL(PHYSFS_ERR_READ_ONLY, 0);
	}

	int Network_stat(void *opaque, const char *path, PHYSFS_Stat *stat) {
		BAIL(PHYSFS_ERR_NOT_FOUND, 0);
	}

	void Network_closeArchive(void *opaque) {
		// TODO: clear the received io
	}


	int dummy_seek(struct PHYSFS_Io *io, PHYSFS_uint64 offset) {
		return 1;
	}
}

extern "C" int PHYSFSNetwork_mount(const char *hostname, const char* port, const char *mountPoint, int appendToPath) {
	OpenArchiveParameters opaque = {
		open_archive_integrity,
		hostname,
		port
	};
	struct PHYSFS_Io io = {
		0,
		&opaque,
		nullptr, // read
		nullptr, // write
		dummy_seek,
	};
	return PHYSFS_mountIo(&io, ".physfs-network", mountPoint, appendToPath);
}

extern "C" const PHYSFS_Archiver PHYSFS_Archiver_Network = {
	0,
	{
		"physfs-network",
		"Read from a TCP socket",
		"Henrique Gemignani",
		"https://github.com/henriquegemignani/physfs-network",
		0,  /* supportsSymlinks */
	},
	Network_openArchive,
	Network_dirTreeEnumerate,
	Network_openRead,
	Network_openWrite,
	Network_openAppend,
	Network_remove,
	Network_mkdir,
	Network_stat,
	Network_closeArchive
};