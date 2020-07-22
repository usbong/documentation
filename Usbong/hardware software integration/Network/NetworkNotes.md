# Network: Notes
## Debian/Ubuntu Linux Operating System (OS)
[Network Configuration](https://wiki.debian.org/NetworkConfiguration#Setting_up_an_Ethernet_Interface)

## I. How to connect to Local Area Network (LAN) via wireless adapter
Execute the following commands in the Terminal Window:
### 1) ifconfig
--> Identify that your computer has a wireless adapter.<br/>
--> It should use the following names: wlan0, mlan0<br/>
--> Note: The wired adapter tends to use the following name: eth0<br/>
### 2) iwlist mlan0 scan | grep ESSID
--> Here we use "mlan0" for the wireless adapter name.<br/>
--> We use the "grep" command for the computer to only show as output rows with the keyword: "ESSID"
### 3) wpa_passphrase \<ssid> [passphrase]
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
--> Add the following rows:<br/><br/>
<b>
auto mlan0<br/>
iface mlan0 inet dhcp<br/>
  wpa-ssid "my_router_ssid"<br/>
  wpa-psk a022d0c8f88de93e4b53e5ee1c5d98cd4171a15bd44cde7499faa294ad795211<br/>
</b>

### 5) ifup mlan0
--> You should receive output messages similar to the following towards the end.<br/><br/>
<b>
  DHCPOFFER from 192.168.11.1<br/>
  DHCPREQUEST on mlan0 to 255.255.255.255 port 67<br/>
  DHCPACK from 192.168.11.1<br/>
  bound to 192.168.11.65 -- renewal in 72617 seconds<br/>
</b>  
--> where: 192.168.11.1 = network gateway<br/>
--> where: 192.168.11.65 = internet protocol (ip) address of the computer<br/>

## Reference
1) https://superuser.com/questions/1068469/cannot-connect-to-network-on-debian?newreg=604705afede645c6b81f30418f7b77e2;<br/>
last accessed: 20200720<br/>
answer by: dpat, 20160424T1141

## II. How to connect to Local Area Network (LAN) via wireless adapter automatically during Computer boot-up
## 1) Execute Actions Steps in "I. How to connect to Local Area Network (LAN) via wireless adapter"
## 2) Execute in the Terminal Window: vi /etc/network/interfaces
--> Note: You may use another text-editor tool, e.g. "gedit", if available, instead of "vi".<br/>
--> Add the following row:<br/><br/>
<b>
allow-hotplug eth0 mlan0
</b>

### Note:
where: eth0 = for the wired ethernet adapter<br/>
where: mlan0 = for the wireless ethernet adapter

### Output:
<b>
allow-hotplug eth0 mlan0<br/>
auto mlan0<br/>
iface mlan0 inet dhcp<br/>
  wpa-ssid "my_router_ssid"<br/>
  wpa-psk a022d0c8f88de93e4b53e5ee1c5d98cd4171a15bd44cde7499faa294ad795211<br/>
</b>

## 3) Execute in the Terminal Window: reboot

## Reference:
1) https://askubuntu.com/questions/22663/how-to-bring-up-network-on-boot-up-when-networkmanager-is-uninstalled;<br/>
last accessed: 20200722<br/>
answer by: user8290, 20110122T1636
2) https://unix.stackexchange.com/questions/390307/startup-debian-9-error-failed-to-start-raise-network-interfaces;<br/>
last accessed: 2020722<br/>
answer by: GAD3R, 20170904T1909

## III. How to quickly transfer files to a Debian/Ubuntu Linux Computer from a Windows Computer
Download and use the software tool, WinSCP.<br/>
https://winscp.net/eng/download.php;<br/>
last accessed: 20200721
### Notes:
1) With Linux Debian 2.6 Operating Systems (OS), set the following in the Advanced Site Settings in WinSCP:<br/>
1.1) Go to "Environment" -> "SCP/Shell"<br/>
1.2) Choose as value for the "Shell:" field: "/bin/bash".


