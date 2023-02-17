#include <Windows.h>
#include <iostream>

int main()
{
    HKEY hKeyClassesRoot, hKeyCurrentConfig, hKeyLocalMachine, hKeyUsers;
    DWORD dwFilter = REG_NOTIFY_CHANGE_LAST_SET;
    HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (RegOpenKeyEx(HKEY_CLASSES_ROOT, NULL, 0, KEY_NOTIFY, &hKeyClassesRoot) == ERROR_SUCCESS)
    {
        std::cout << "Monitoring changes in HKEY_CLASSES_ROOT" << std::endl;
    }
    if (RegOpenKeyEx(HKEY_CURRENT_CONFIG, NULL, 0, KEY_NOTIFY, &hKeyCurrentConfig) == ERROR_SUCCESS)
    {
        std::cout << "Monitoring changes in HKEY_CURRENT_CONFIG" << std::endl;
    }
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, NULL, 0, KEY_NOTIFY, &hKeyLocalMachine) == ERROR_SUCCESS)
    {
        std::cout << "Monitoring changes in HKEY_LOCAL_MACHINE" << std::endl;
    }
    if (RegOpenKeyEx(HKEY_USERS, NULL, 0, KEY_NOTIFY, &hKeyUsers) == ERROR_SUCCESS)
    {
        std::cout << "Monitoring changes in HKEY_USERS" << std::endl;
    }

    while (true)
    {
        if (RegNotifyChangeKeyValue(hKeyClassesRoot, TRUE, dwFilter, hEvent, TRUE) == ERROR_SUCCESS)
        {
            std::cout << "Registry Key Changed in HKEY_CLASSES_ROOT!" << std::endl;
        }
        if (RegNotifyChangeKeyValue(hKeyCurrentConfig, TRUE, dwFilter, hEvent, TRUE) == ERROR_SUCCESS)
        {
            std::cout << "Registry Key Changed in HKEY_CURRENT_CONFIG!" << std::endl;
        }
        if (RegNotifyChangeKeyValue(hKeyLocalMachine, TRUE, dwFilter, hEvent, TRUE) == ERROR_SUCCESS)
        {
            std::cout << "Registry Key Changed in HKEY_LOCAL_MACHINE!" << std::endl;
        }
        if (RegNotifyChangeKeyValue(hKeyUsers, TRUE, dwFilter, hEvent, TRUE) == ERROR_SUCCESS)
        {
            std::cout << "Registry Key Changed in HKEY_USERS!" << std::endl;
        }

        WaitForSingle
