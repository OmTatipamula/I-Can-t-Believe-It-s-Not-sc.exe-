#pragma comment(lib, "advapi32.lib")

#include <Windows.h>
#include <iostream>
#include <sstream>

#include "create_service.h"


DWORD MapServiceType(const std::string& svcType, const std::string& interactType)
{
    if (svcType == "own")
        return SERVICE_WIN32_OWN_PROCESS;
    else if (svcType == "share")
        return SERVICE_WIN32_SHARE_PROCESS;
    else if (svcType == "kernel")
        return SERVICE_KERNEL_DRIVER;
    else if (svcType == "filesys")
        return SERVICE_FILE_SYSTEM_DRIVER;
    else if (svcType == "rec")
        return SERVICE_RECOGNIZER_DRIVER;
    else if (svcType == "interact")
    {
        // When "interact" is specified, the interactType must be either "own" or "share".
        if (interactType == "own")
            return SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
        else if (interactType == "share")
            return SERVICE_WIN32_SHARE_PROCESS | SERVICE_INTERACTIVE_PROCESS;
        else
        {
            // Fallback if interactType isn't valid.
            return SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
        }
    }
    // Default
    return SERVICE_WIN32_OWN_PROCESS;
}

DWORD MapStartType(const std::string& startType)
{
    if (startType == "boot")
        return SERVICE_BOOT_START;
    else if (startType == "system")
        return SERVICE_SYSTEM_START;
    else if (startType == "auto" || startType == "delayed-auto")
        return SERVICE_AUTO_START;
    else if (startType == "demand")
        return SERVICE_DEMAND_START;
    else if (startType == "disabled")
        return SERVICE_DISABLED;
    return SERVICE_DEMAND_START;
}

DWORD MapErrorControl(const std::string& errorControl)
{
    if (errorControl == "normal")
        return SERVICE_ERROR_NORMAL;
    else if (errorControl == "severe")
        return SERVICE_ERROR_SEVERE;
    else if (errorControl == "critical")
        return SERVICE_ERROR_CRITICAL;
    else if (errorControl == "ignore")
        return SERVICE_ERROR_IGNORE;
    return SERVICE_ERROR_NORMAL;
}

// Convert dependency string (with '/' delimiters) to a double-null-terminated multi-string.
// see: https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-createservicea
// 
std::string ConvertDependencies(const std::string& deps)
{
    if (deps.empty())
        return std::string();
    
    std::istringstream iss(deps);
    std::string token;
    std::string multiStr;
    
    while (std::getline(iss, token, '/'))
    {
        if (!token.empty())
        {
            multiStr.append(token);
            multiStr.push_back('\0'); // Null-terminate each dependency
        }
    }
    multiStr.push_back('\0'); // Double-null termination
    return multiStr;
}

// knock off of Microsoft's example code but a lot worse and with key features broken
void createService(const CreateOptions &opts)
{
    SC_HANDLE hSCManager = OpenSCManagerA(
        opts.serverName.empty() ? NULL : opts.serverName.c_str(),
        NULL,
        SC_MANAGER_CREATE_SERVICE
    );
    
    if (hSCManager == NULL)
    {
        std::cerr << "OpenSCManager failed (" << GetLastError() << ")\n";
        return;
    }
    
    DWORD dwServiceType = MapServiceType(opts.serviceType, opts.interactType);
    DWORD dwStartType   = MapStartType(opts.startType);
    DWORD dwErrorCtrl   = MapErrorControl(opts.errorControl);
    
    std::string depsMultiStr = ConvertDependencies(opts.depend);
    LPSTR lpDependencies = depsMultiStr.empty() ? NULL : const_cast<LPSTR>(depsMultiStr.c_str());
    
    DWORD dwTagId = 0;
    DWORD *lpTagId = (opts.tag == "yes") ? &dwTagId : NULL;
    
    LPCSTR pszDisplayName = opts.displayname.empty() ? opts.serviceName.c_str() : opts.displayname.c_str();
    
    SC_HANDLE hService = CreateServiceA(
        hSCManager,                              // SCManager database handle
        opts.serviceName.c_str(),                // Name of service to install
        pszDisplayName,                          // Display name
        SERVICE_ALL_ACCESS,                      // Desired access
        dwServiceType,                           // Service type
        dwStartType,                             // Start type
        dwErrorCtrl,                             // Error control type
        opts.binpath.c_str(),                    // Service's binary path
        opts.group.empty() ? NULL : opts.group.c_str(), // Load order group
        lpTagId,                                 // Tag ID pointer (optional)
        lpDependencies,                          // Dependencies
        opts.obj.c_str(),                        // Service start name
        opts.password.empty() ? NULL : opts.password.c_str() // Password
    );
    
    if (hService == NULL)
    {
        std::cerr << "CreateService failed (" << GetLastError() << ")\n";
        CloseServiceHandle(hSCManager);
        return;
    }
    
    std::cout << "Service created successfully.\n";
    
    if (opts.startType == "delayed-auto")
    {
        SERVICE_DELAYED_AUTO_START_INFO delayedInfo;
        delayedInfo.fDelayedAutostart = TRUE;
        if (!ChangeServiceConfig2A(
                hService,
                SERVICE_CONFIG_DELAYED_AUTO_START_INFO,
                (LPBYTE)&delayedInfo))
        {
            std::cerr << "ChangeServiceConfig2 failed (" << GetLastError() << ")\n";
        }
        else
        {
            std::cout << "Delayed auto-start configured.\n";
        }
    }
    
    // Cleanup handles.
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
}