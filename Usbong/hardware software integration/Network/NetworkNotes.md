# Network: Notes
## Debian/Ubuntu Linux Operating System (OS)
[Network Configuration](https://wiki.debian.org/NetworkConfiguration#Setting_up_an_Ethernet_Interface)

## How to connect to Local Area Network (LAN) via wireless adapter
Execute the following commands in the Terminal Window:
### 1) ifconfig
--> Identify that your computer has a wireless adapter.<br/>
--> It should use the following names: wlan0, mlan0<br/>
--> Note: The wired adapter tends to use the following name: eth0<br/>
### 2) iwlist mlan0 scan | grep ESSID
--> Here we use "mlan0" for the wireless adapter name.<br/>
--> We use the "grep" command for the computer to only show as output rows with the keyword: "ESSID"
### 3) wpa_passphrase <ssid> [passphrase]
--> where: <ssid> = the wireless router's SSID<br/>
--> where: [passphrase] = the passphrase to connect to the wireless router
  
#### Output:

<b>
network={<br/>
  ssid="my_router_ssid"<br/>
  #psk="my_router_passphrase"<br/>
  psk=a022d0c8f88de93e4b53e5ee1c5d98cd4171a15bd44cde7499faa294ad795211<br/>
}
</b>

### 4) vi /etc/network/interfaces
--> Note: You may use another text-editor tool, e.g. "gedit", if available, instead of "vi".<br/>
--> Add the following rows:<br/>
<b>
auto mlan0<br/>
iface mlan0 inet dhcp<br/>
  wpa-ssid "my_router_ssid"<br/>
  wpa-psk a022d0c8f88de93e4b53e5ee1c5d98cd4171a15bd44cde7499faa294ad795211<br/>
</b>

### 5) ifup mlan0
--> You should receive output messages similar to the following towards the end.<br/>
<b>
  DHCPOFFER from 192.168.11.1<br/>
  DHCPREQUEST on mlan0 to 255.255.255.255 port 67<br/>
  DHCPACK from 192.168.11.1<br/>
  bound to 192.168.11.65 -- renewal in 72617 seconds<br/>
</b>  
--> where: 192.168.11.1 = network gateway<br/>
--> where: 192.168.11.65 = internet protocol (ip) address of the computer<br/>

## Reference
1) https://superuser.com/questions/1068469/cannot-connect-to-network-on-debian?newreg=604705afede645c6b81f30418f7b77e2;
last accessed: 20200720<br/>
answer by: dpat, 20160424T1141
