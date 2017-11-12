#include "physfs-network.h"

#define BAIL(e, r) do { if (e) PHYSFS_setErrorCode(e); return r; } while (0)

namespace {
	void *Network_openArchive(PHYSFS_Io *io, const char *name, int forWriting, int *claimed) {

		if (forWriting) {
			BAIL(PHYSFS_ERR_READ_ONLY, nullptr);
		}

		return nullptr;
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
}


extern "C" const PHYSFS_Archiver PHYSFS_Archiver_Network = {
	0,
	{
		nullptr,
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