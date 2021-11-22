# NodeMCU_HomeKit
This porject was made for Apple Homekit device.<br>
GPIO5 for relay control and GPIO4 for force WiFi update switch.<br>
When power up, will read WiFi SSID and Password from emulated EEPROM.<br>
if SSID and Password is empty, go WiFi confiure step.<br>
if SSID and Password existed, will try to connect to WiFi AP.<br>
if connect to WiFi AP success, go Homekit configure and process.<br>
else go WiFi configure step.<br>
<br>
## WiFi configure process
enable AP mode.<br>
connect to ESP WiFi AP and launch 192.168.4.1 in browser.<br>
input SSID and password. will check if WiFi connection is ok.<br>
reset dvice when configure finished.<br>
will wrtie SSID and password to emulated EEPROM.<br>

## Library modification
since HomeKit library used user storage space as EEPORM library did, the user data will be overwrite when library initialized.
need to change HomeKit user storage address to avoid overwrite.
// src/storage.c
//#define HOMEKIT_EEPROM_PHYS_ADDR ((uint32_t) (&_EEPROM_start) - 0x40200000)
#define HOMEKIT_EEPROM_PHYS_ADDR ((uint32_t) (&_EEPROM_start) - 0x40200000 - 0x1000)

by Patrick Lin @ Taiwan<br>
2021/11/16
