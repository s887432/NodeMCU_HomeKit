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

by Patrick Lin @ Taiwan<br>
2021/11/16
