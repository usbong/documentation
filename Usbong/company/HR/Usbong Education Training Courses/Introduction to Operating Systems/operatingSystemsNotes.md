# Operating Systems Notes
## 1) Free Berkeley Software Distribution (BSD)
--> https://www.freebsd.org/; last accessed: 20200816<br/>
### 1.1) Recommended Reading: 
https://www.freebsd.org/doc/en_US.ISO8859-1/articles/explaining-bsd/index.html; last accessed: 20200816

### 1.2) Additional Notes: FreeBSD Installation Using Linux Machine
#### 1.2.1) Show list of all connected block devices, e.g. Universal Serial Bus (USB) Memory Storage
<b>lsblk</b><br/>
#### Reference:
https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/bsdinstall-pre.html;<br/>
last accessed: 20200830
<br/>
#### 1.2.2) Write Image in USB Memory Storage
<b>sudo dd if=FreeBSD-12.1-RELEASE-amd64-20200806-r363918-memstick.img of=/dev/sdb bs=1M conv=sync</b><br/>
##### where: /dev/sdb = target USB device

#### 1.2.2.1) Notes:
RELEASE : MOST STABLE<br/>
STABLE : STABLE<br/>
CURRENT : LEAST STABLE

#### 1.2.2.2) References:
1.2.2.2.1) https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/bsdinstall-pre.html;<br/>
last accessed: 20200830<br/>
<br/>
1.2.2.2.2) https://forums.freebsd.org/threads/current-vs-stable-vs-release.3716/;<br/>
last accessed: 20200909

#### 1.2.3) If you experience problems installing image file using USB Memory Storage version 3.*, e.g. 3.1, verify using USB version 2.0
--> <b>Example Problems:</b> stuck in loading boot device, does not reach installation program, shows usb device error<br/> 
--> Verified this solution solved the aforementioned installation problem with NetBSD.<br/>
--> However, the operating system remained uninstalled due to problem re-formatting harddisk.<br/>
--> <b>Note:</b> Installation problem occured with BSD variations, e.g. FreeBSD, FuryBSD, FreeNAS, NetBSD, OpenBSD.

#### Reference:
https://news.ycombinator.com/item?id=17582465;<br/>
last accessed: 20200909

### 1.2.4) The following actions quickly caused the Operating System to be installed and usable.
Verified with [LUBUNTU 20.04](lubuntu.me) and [Virtual Box 6.1](https://www.virtualbox.org/).<br/>
--> Download and install Virtual Box.<br/>
#### 1.2.4.1) Verified with FreeBSD 12.1
--> Download and extract <b>FreeBSD-12.1-RELEASE-amd64.vmdk.xz</b><br/>
https://download.freebsd.org/ftp/releases/VM-IMAGES/12.1-RELEASE/amd64/Latest/; last accessed: 20200911<br/>
--> Choose the Virtual Machine Disk (VMDK) Image file.

#### 1.2.4.2) Verified with OpenBSD (install67.iso)
--> Download .iso file.<br/>
https://www.openbsd.org/faq/faq4.html#Download; last accessed: 20200911<br/>
--> Choose to boot the .iso file.

##### Additional Notes:
1) Checksum Commands available in the <b>Downloading BSD</b> section:<br/>
https://www.openbsd.org/faq/faq4.html#Download; last accessed: 20200911<br/>
2) ISO = International Organization for Standardization
