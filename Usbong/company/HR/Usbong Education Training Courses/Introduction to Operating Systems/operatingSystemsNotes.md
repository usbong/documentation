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
<b>sudo dd if=FreeBSD-12.1-STABLE-amd64-20200806-r363918-memstick.img of=/dev/sdb bs=1M conv=sync</b><br/>
##### where: /dev/sdb = target USB device

#### Reference:
https://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/bsdinstall-pre.html;<br/>
last accessed: 20200830

#### 1.2.3) If you experience problems installing image file using USB Memory Storage version 3.*, e.g. 3.1, verify using USB version 2.0
--> <b>Example Problems:</b> stuck in loading boot device, does not reach installation program, shows usb device error<br/> 
--> Verified this solution solved the installation problem with NetBSD.<br/>
--> <b>Note:</b> Installation problem occured with BSD variations, e.g. FreeBSD, FuryBSD, FreeNAS, NetBSD.

#### Reference:
https://news.ycombinator.com/item?id=17582465;<br/>
last accessed: 20200909
