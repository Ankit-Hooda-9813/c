import win32api
import win32con
import winnt
import pythoncom
import win32com.client

def registry_change_detector():
    pythoncom.CoInitialize()
    registry = win32com.client.Dispatch("WbemScripting.SWbemLocator").ConnectServer(".", "root\default").Get("StdRegProv")

    # HKEY_LOCAL_MACHINE\Software
    hKey = win32con.HKEY_LOCAL_MACHINE
    subKey = "Software"

    handle = win32api.RegOpenKeyEx(hKey, subKey, 0, win32con.KEY_NOTIFY)

    while True:
        print('checking...')
        result = win32api.RegNotifyChangeKeyValue(handle, True, winnt.REG_NOTIFY_CHANGE_NAME | winnt.REG_NOTIFY_CHANGE_LAST_SET, None, False)
        print('checking...')
        if result == 0:
            print("Change detected")

if __name__ == "__main__":
    registry_change_detector()
