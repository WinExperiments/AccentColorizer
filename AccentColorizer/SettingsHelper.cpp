#include "SettingsHelper.h"
#include "SystemHelper.h"

#include <VersionHelpers.h>

#define DEFAULT_PROGRESS_BAR_COLORIZATION FALSE

enum REGISTRY_OPTION_STATUS
{
    REGISTRY_OPTION_ENABLED,
    REGISTRY_OPTION_DISABLED,
    REGISTRY_OPTION_NOT_SET
};

REGISTRY_OPTION_STATUS
GetRegistryOptionStatus(LPCWSTR key, LPCWSTR value)
{
    HKEY hKey;
    RegOpenKeyEx(
        HKEY_CURRENT_USER,
        key, 0, KEY_READ, &hKey
    );

    if (!hKey)
    {
        return REGISTRY_OPTION_NOT_SET;
    }

    DWORD dwBufferSize(sizeof(DWORD));
    DWORD nResult(0);
    LONG nError = RegQueryValueEx(
        hKey, value, 0, NULL,
        reinterpret_cast<LPBYTE>(&nResult),
        &dwBufferSize
    );

    RegCloseKey(hKey);

    return ERROR_SUCCESS == nError 
        ? REGISTRY_OPTION_ENABLED
        : REGISTRY_OPTION_DISABLED;
}

bool IsMenuColorizationEnabled()
{
    if (g_winver < WIN_10)
    {
        return true;
    }

    return INVALID_FILE_ATTRIBUTES == GetFileAttributes(L"C:\\Windows\\ContextMenuNormalizer.exe")
        && GetLastError() == ERROR_FILE_NOT_FOUND;
}

bool IsProgressBarColorizationEnabled()
{
    REGISTRY_OPTION_STATUS status = GetRegistryOptionStatus(L"SOFTWARE\\AccentColorizer", L"ColorizeProgressBar");
    if (status == REGISTRY_OPTION_NOT_SET) {
        return DEFAULT_PROGRESS_BAR_COLORIZATION;
    }
    return status == REGISTRY_OPTION_ENABLED;
}