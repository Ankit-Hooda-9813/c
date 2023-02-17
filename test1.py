    import win32api
    import win32con
    import win32com.client
    import logging

    logging.basicConfig(level=logging.DEBUG, format='%(asctime)s,%(msecs)03d %(levelname)-5.5s [%(name)s] %(message)s', filename='watchRegistry.log')
    log = logging.getLogger()

    def watch_registry():
        hives = [win32con.HKEY_LOCAL_MACHINE, win32con.HKEY_CURRENT_USER]

        for hive in hives:
            root_key = win32api.RegOpenKeyEx(hive, "", 0, win32con.KEY_READ)
            index = 0
            while True:
                try:
                    key_name = win32api.RegEnumKey(root_key, index)
                    index += 1
                    sub_key = win32api.RegOpenKeyEx(root_key, key_name, 0, win32con.KEY_ALL_ACCESS)
                    log.debug(f"Sub key: {key_name}")
                    watch_registry_new(sub_key)
                except WindowsError as e:
                    break


    def watch_registry_new(root_key):
        key_index = 0
        while True:
            try:
                key_name = win32api.RegEnumKeyEx(root_key, key_index)
            except Exception as e:
                break
            sub_key = win32api.RegOpenKeyEx(root_key, key_name, 0, win32con.KEY_ALL_ACCESS)
            log.debug(f"Sub key: {key_name}")
            watch_registry_new(sub_key)
            win32api.RegCloseKey(sub_key)
            key_index += 1

    watch_registry()
    # watch_registry(win32con.HKEY_LOCAL_MACHINE)


