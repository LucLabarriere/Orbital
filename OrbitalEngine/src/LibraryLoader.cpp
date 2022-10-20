#include "OrbitalEngine/LibraryLoader.h"
#include "OrbitalTools/Files.h"
#include "OrbitalLogger/Logger.h"

#ifdef _WIN32
#include <windows.h>
#include <cstdlib>

namespace Orbital
{
    void* LibraryLoader::OpenLibrary(const char* path)
    {
        return LoadLibrary(path);
    }

    void LibraryLoader::CloseLibrary(void* libraryHandle)
    {
        FreeLibrary(static_cast<HINSTANCE>(libraryHandle));
    }

    void* LibraryLoader::GetFunction(void *libraryHandle, const char *functionName)
    {
        return createFunc = GetProcAddress(
            static_cast<HINSTANCE>(libraryHandle), functionName
        );
    }

    const char* LibraryLoader::GetError()
    {
        return dlerror();
    }

    void LibraryLoader::LogError()
    {
        DWORD errCode = GetLastError();
        char *err;
        if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           errCode,
                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
                           (LPTSTR) &err,
                           0,
                           NULL))
            return;

        static char buffer[MAX_PATH];
        _snprintf(buffer, sizeof(buffer), "ERROR: %s: %s\n", "Windows", err);

        Logger::Error(buffer);

        LocalFree(err);
    }
}

#else // Linux

#include <dlfcn.h>
#include <cstdlib>

namespace Orbital
{
    void* LibraryLoader::OpenLibrary(const char* path)
    {
        return dlopen(path, RTLD_LAZY);
    }

    void LibraryLoader::CloseLibrary(void* libraryHandle)
    {
        dlclose(libraryHandle);
    }

    void* LibraryLoader::GetFunction(void *libraryHandle, const char *functionName)
    {
        return dlsym(libraryHandle, functionName);
    }

    const char* LibraryLoader::GetError()
    {
        return dlerror();
    }

    void LibraryLoader::LogError()
    {
        Logger::Error(dlerror());
    }
}

#endif
