#pragma once

#ifdef _WIN32
#error TODO: Implement PathTools for Windows
#endif

#include <cstring>
#include <linux/limits.h>
#include <unistd.h>

class PathTools {
public:
	static const char* get_executable_directory() {
		static char path[PATH_MAX];

		if (readlink("/proc/self/exe", path, sizeof(path) - 1) == -1) {
			return nullptr;
		}
		path[sizeof(path) - 1] = '\0';

		char* last_slash = strrchr(path, '/');
		if (last_slash) {
			*last_slash = '\0';
		}
		return path;
	}

private:
};
