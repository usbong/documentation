# Network: Notes
## Debian/Ubuntu Linux Operating System (OS)
[Network Configuration](https://wiki.debian.org/NetworkConfiguration#Setting_up_an_Ethernet_Interface)

## How to connect to Local Area Network (LAN) via wireless adapter
Execute the following commands:
### 1) ifconfig
--> Identify that your computer has a wireless adapter.<br/>
--> It should use the following names: wlan0, mlan0<br/>
--> Note: The wired adapter tends to use the following name: eth0<br/>
### 2) iwlist mlan0 scan | grep ESSID
--> Here we use "mlan0" for the wireless adapter name.<br/>
--> We use the "grep" command for the computer to only show as output rows with the keyword: "ESSID"
### 3) wpa_passphrase <ssid> [passphrase]
--> where: <ssid> = the wireless router's SSID<br/>
--> where: [passphrase] = the passphrase to connect to the wireless router<br/>
#### Output:
network={<br/>
  ssid="my_router_ssid"<br/>
  #psk="my_router_passphrase"<br/>
  psk=a022d0c8f88de93e4b53e5ee1c5d98cd4171a15bd44cde7499faa294ad795211<br/>
}
  
TO-DO: -add: the rest of the instructions
