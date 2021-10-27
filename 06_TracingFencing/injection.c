#define _GNU_SOURCE
#include <dlfcn.h> // for dlsym
#include <errno.h> // for EPERM
#include <string.h> // for strstr

typedef int (*injection_t)(const char* old_path, const char* new_path);

int rename(const char* old_path, const char* new_path)
{
    injection_t original_rename = dlsym(RTLD_NEXT, "rename");
    if (strstr(old_path, "PROTECT") != NULL) {
        errno = EPERM;
        return -1;
    }

    return original_rename(old_path, new_path);
}