# WirelessPalaControl

This project uses "palazzetti library" and a D1 Mini to control Fumis based stove using :
 - HTTP GET requests
 - MQTT

D1 mini is cabled to the stove using an adapter board.  
It communicates using Serial protocol on ESP8266 alternative pins : D7(GPIO13) as RX / D8(GPIO15) as TX

## Compatibility

It appears that Fumis Controller is used by those brands for their stoves : 

* Palazzetti (All)
* Jotul (tested successfully on PF 620 & 720)
* TurboFonte
* Godin
* Fonte Flamme
* Invicta
* Alpis
* Faizen
* HETA

If you have this controller in your stove, it's likely to be compatible.  
![Fumis Controller](https://raw.github.com/Domochip/WirelessPalaControl/master/img/fumis.png)

## Build your adapter

You can use this adapter with:
 - a D1 Mini to build a WirelessPalaControl
 - another controller with serial interface
 - an USB-Serial adapter and a computer to monitor or upgrade your stove

It is designed by Palazzetti using a Si8621 (Silicon Labs Isolator) to provide electrical isolation between uController and Stove electronic.  
This design uses exact same schematic and components.


All files are inside `schematic` subfolder and has been designed with KiCad (free and open source)

### Schematic

![WirelessPalaControl schematic](https://raw.github.com/Domochip/WirelessPalaControl/master/img/schematic.png)

### PCB

![WirelessPalaControl PCB](https://raw.github.com/Domochip/WirelessPalaControl/master/img/pcb-top.png)![WirelessPalaControl PCB2](https://raw.github.com/Domochip/WirelessPalaControl/master/img/pcb-bottom.png)

![WirelessPalaControl 3boards](https://raw.github.com/Domochip/WirelessPalaControl/master/img/3boards.png)

*We produced a small batch of this adapter for test/debugging and our personal use.
If you are interested, please PM.*

### Print your box

Box project (Fusion 360 & STL) can be found into `box` folder

![WirelessPalaControl box](https://raw.github.com/Domochip/WirelessPalaControl/master/img/box.png)

### Code/Compile/Flash

Source code can be compiled using VisualStudioCode/Platformio and flashed onto a D1 Mini  
Or  
Download latest release in Release section

### Connect

/!\ **You need to use an RJ11 standard phone cable.** /!\  
Those are **crossed** like this  
![WirelessPalaControl rj11](https://raw.github.com/Domochip/WirelessPalaControl/master/img/rj11-pinout.png)

Most of stove have an RJ11/RJ12 connector for PalaControl connection.  
If you don't have it, you need to cable it using a splitter to connect screen and palaControl at the same time :  
![WirelessPalaControl cabling](https://raw.github.com/Domochip/WirelessPalaControl/master/img/cabling.png)

Splitter and additional cable can be found on Aliexpress (search for "6p6c splitter" and "rj12 cable").  
The splitter should correspond to this small schematic :  
![WirelessPalaControl schematic-splitter](https://raw.github.com/Domochip/WirelessPalaControl/master/img/schematic-splitter.png)

## Run

### First Boot

During First Boot, the ESP boot in Access Point Mode

- Network SSID : `WirelessPalaControlXXXX`
- Password : `PasswordPalaControl`
- ESP IP : `192.168.4.1`

Connect to this network and then configure it.

### Configuration

WirelessPalaControl offers you some webpages in order to configure it :

- `Status` return you the current status of the module (and the Serial Number of your stove):  
![status screenshot](https://raw.github.com/Domochip/WirelessPalaControl/master/img/status.png)  
**Then 1 minute later, other stove information appears (default upload period)**
![status2 screenshot](https://raw.github.com/Domochip/WirelessPalaControl/master/img/status2.png)

- `Config` allows you to change configuration :  
![config screenshot](https://raw.github.com/Domochip/WirelessPalaControl/master/img/config.png)  
  **ssid & password** : IDs of your Wifi Network  
  **hostname** : name of ESP on the network  
  **IP,GW,NetMask,DNS1&2** : Fixed IP configuration  
![configMQTT screenshot](https://raw.github.com/Domochip/WirelessPalaControl/master/img/configMQTT.png)  
  Fill-in MQTT broker information

- `Firmware` allows you to flash a new firmware version :  
![firmware screenshot](https://raw.github.com/Domochip/WirelessPalaControl/master/img/firmware.png)

- `Discover` allows you to find all DomoChip devices on your network :  
![discover screenshot](https://raw.github.com/Domochip/WirelessPalaControl/master/img/discover.png)

## Use it

### MQTT

MQTT requests can be send to /cmd topic once MQTT is configured

MQTT Command list : 
- `CMD+ON` will turn stove ON
- `CMD+OFF` will turn stove OFF
- `SET+POWR+3` will set power (1-5)
- `SET+SETP+20` will set Set Point (desired temperature)
- `SET+RFAN+2` will set Room Fan value (0-5;6=Max;7=Auto)

MQTT infos published every "Upload Period":
- `STATUS` status of the stove
- `LSTATUS` status of the stove
- `T1` temperature of the stove
- `T2` temperature of the stove
- `T3` temperature of the stove
- `T4` temperature of the stove
- `T5` temperature of the stove
- `F1V` fan value
- `F2V` fan value
- `F2L` fan value
- `F2LF` fan value
- `F3L` fan value
- `F4L` fan value
- `IGN` ignition counter
- `IGNERRORS` ignition error counter
- `POWERTIME` total heating time (hour)
- `HEATTIME` ??? (hour)
- `SERVICETIME` heating time since last maintenance (hour)
- `ONTIME` time from last power ON (hour)
- `OVERTMPERRORS` overtemperature error counter
- `STOVE_DATETIME` date of the stove
- `STOVE_WDAY` week day of the stove
- `SETP` current Set Point (desired temperature)
- `PQT` wood pellet consumption
- `PWR` current power (1-5)
- `FDR` feeder
- `DP_TARGET` delta pressure target
- `DP_PRESS` actual delta pressure

### HTTP

HTTP GET requests can be send directly and should follow this syntax : **http://*{IP}*/cgi-bin/sendmsg.lua?cmd=*{command}***

HTTP GET Command list : 

- `GET+STDT` will return static data
- `GET+ALLS` will return all status data
- `GET+STAT` will return status of the stove
- `GET+TMPS` will return temperatures of the stove
- `GET+FAND` will return Fan values
- `GET+SETP` will return current Set Point (desired temperature)
- `GET+POWR` will return current power (1-5)
- `GET+CUNT` will return some counters
- `GET+CNTR` will return some counters (same as GET+CUNT)
- `GET+DPRS` will return delta pressure data
- `GET+TIME` will return stove clock data
- `GET+IOPT` will return IO ports status
- `GET+SERN` will return stove Serial Number
- `GET+MDVE` will return stove model and fw version
- `GET+CHRD` will return chrono data
- `GET+PARM+92` will return parameter (ex : 92=pellet type (1-3))
- `GET+HPAR+57` will return hidden parameter (ex : 57=% of pellet to feed for pellet type 3)
---
**WirelessPalaControl specific commands**
- `BKP+PARM+CSV` will return all parameters in CSV format
- `BKP+PARM+JSON` will return all parameters in JSON format
- `BKP+HPAR+CSV` will return all hidden parameters in CSV format
- `BKP+HPAR+JSON` will return all hidden parameters in JSON format
---
- `CMD+ON` will turn stove ON
- `CMD+OFF` will turn stove OFF
- `SET+POWR+3` will set power (1-5)
- `SET+PWRU` will increase power by 1 unit
- `SET+PWRD` will decrease power by 1 unit
- `SET+SETP+20` will set Set Point (desired temperature)
- `SET+STPU` will increase Set Point by 1 unit
- `SET+STPD` will decrease Set Point by 1 unit
- `SET+RFAN+7` will set Room Fan value (0-5;6=Max;7=Auto)
- `SET+FN2U` will increase Room Fan by 1 unit
- `SET+FN2D` will decrease Room Fan by 1 unit
- `SET+FN3L+0` will set Room Fan 3 value (0-5)
- `SET+FN4L+0` will set Room Fan 4 value (0-5)
- `SET+SLNT+0` will set Silent mode value (0-1)
- `SET+CSST+0` will set Chrono Status value (0-1)
- `SET+CSTH+2+18` will set Chrono Program Start Hour (1-6) (0-23)
- `SET+CSTM+2+30` will set Chrono Program Start Minute (1-6) (0-59)
- `SET+CSPH+2+22` will set Chrono Program Stop Hour (1-6) (0-23)
- `SET+CSPM+2+45` will set Chrono Program Stop Minute (1-6) (0-59)
- `SET+CSET+2+19` will set Chrono Program Set Point (1-6) (desired temperature)
- `SET+CDAY+7+3+6` will set Chrono Program for week day (Day-Mem-Prog) (1-7) (1-3) (1-6)
- `SET+CPRD+1+19+18+30+22+45` will set Chrono Program data (Prog-Temp-StartH-StartM-StopH-StopM) (1-6) (temperature) (0-23) (0-59) (0-23) (0-59)
- `SET+PARM+92+2` will set parameter 92 to value 2 (ex : 92=pellet type (1-3))
- `SET+HPAR+57+95` will set hidden parameter 57 to value 95 (ex : 57=% of pellet to feed for pellet type 3)
---
**WirelessPalaControl specific commands**
- `SET+STPF+19.8` will set Set Point with a 0.2° precision (depend of your stove model)
