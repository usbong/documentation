# Printers and Scanners
## 1) Hewlett-Packard (HP) Deskjet Ink Advantage 2010 LINUX Drivers (Printer)
https://developers.hp.com/hp-linux-imaging-and-printing; last accessed: 20200620

### Additional Note
If installation using LINUX drivers unsuccessful due to dependency requirements, e.g. python library, verify executing the following actions:<br/>
#### 1.1) In Terminal Window... <br/>
<b>sudo apt-get install printer-driver-all</b><br/>
<b>sudo systemctl restart cups</b>

#### 1.2) Preferences -> Printers -> Add<br/>

#### Reference:
https://askubuntu.com/questions/1046087/error-during-the-cups-operation-client-error-document-format-not-supported;
last accessed: 202100401<br/>
answer by: Gayan Weerakutti, 20201031T1119<br/>
edited by: Kulfy, 20201031T1931<br/>
--> verified: with LUBUNTU (LTS 20.04)<br/>

## Problem & Answer
<b>Problem:</b> Printer prints blank page when using LibreOffice Writer (ver: 6.4.3.2) on LUBUNTU (ver: 20.04)<br/>
<b>Answer:</b><br/>
1.1) Go to: Tools, Options, Print<br/>
1.2) Unset: in Defaults, "PDF as standard print job format"<br/>
<br/>
Done!<br/>
<br/>
<b>Reference:</b> https://ask.libreoffice.org/en/question/68113/print-a-blank-page-when-printing-a-word-doc-from-libreoffice/;<br/>
last accessed: 20200622<br/>
answer by: Dave

## 2) Samsung SCX-4521F Linux Drivers (Printer and Scanner)
https://support.hp.com/us-en/drivers/selfservice/samsung-scx-4521-laser-multifunction-printer-series/16462424/model/19135313; last accessed: 20200623

## Commands
### 2.1) Install Command<br/>
2.1.1) Extract the "uld...tar.gz" zipped file that you downloaded.<br/>
2.1.2) Inside the extracted "uld" folder, write the following command in the Terminal Window.<br/>
<br/>
<b>sudo ./install.sh</b><br/>
<br/>
<b>Notes:</b><br/>
1) There are 10 sections. You press the "Enter" key to scroll down.<br/>
2) Press "y" to agree and to install.<br/>
### 2.2) Verify Command
Verify that the Linux machine identifies and classifies device to exist<br/>
<br/>
<b>scanimage -L</b>
<br/>
<br/>
<b>Output:</b><br/>
<br/>
<b>device 'smfp:usb;...' is a Samsung SCX-4x21 Series on USB Scanner</b><br/>
<br/>
where: "..." are identification numbers/letters<br/>

### 2.3) Scan Command<br/>
<b>scanimage > outputImage.pnm</b><br/>
<br/>
where: ".pnm" is the image file format<br/>
<br/>
<b>Note:</b> You can also use .jpeg as output, instead of .pnm<br/>
<b>Example:</b><br/>
<b>scanimage --format=jpeg > outputImage.jpeg</b>

### References:
1) https://bugs.launchpad.net/simple-scan/+bug/1539933; last accessed: 20200623<br/>
2) https://ubuntuforums.org/archive/index.php/t-2130330.html; last accessed: 20200623

### Problem & Answer
<b>Problem:</b> Scan command outputs "Segmentation fault (core dumped)" on LUBUNTU (ver: 20.04)<br/>
<b>Answer:</b><br/>
1.1) Before using the Scan command, write and enter the following instructions in the Terminal Window. This is to verify that the Linux machine indentifies and classifies device to exist.<br/>
<br/>
<b>scanimage -L</b>
<br/>
<br/>
1.2) If you receive the following output, you should now be able to use the Scan command successfully.<br/>
<br/>
<b>device 'smfp:usb;...' is a Samsung SCX-4x21 Series on USB Scanner</b><br/>
<b>device 'xerox_mfp:libusb:...' is a Samsung ORION multi-function peripheral</b><br/>
<br/>
Done!<br/>
<br/>

## 3) Brother DCP Series Linux Drivers (Printer and Scanner)
### 3.1) Brother DCP Series Model Name Identification
3.1.1) DCP-165C<br/>
https://support.brother.com/g/b/downloadhowto.aspx?c=ph&lang=en&prod=dcp165c_all&os=128&dlid=dlf006893_000&flang=4&type3=625; last accessed: 20201014<br/>
<br/>
3.1.2) DCP-L2540DW<br/>
https://support.brother.com/g/b/downloadlist.aspx?c=ph&lang=en&prod=dcpl2540dw_us_as&os=128; last accessed: 20201110<br/>
<br/>
<b>Note:</b><br/>
1) You will need to install the Linux Driver for each Brother DCP Machine that is connected even to the same computer.

### 3.2) Scan Command<br/>
<b>scanimage --format=jpeg > outputImage.jpeg</b><br/>
<br/>
where: ".jpeg" is the image file format

## 3.3) Problem & Answer
<b>3.3.1) Problem:</b> iPAD Tablet Computer connected to network does NOT cause Printer to print<br/>
Printer connected to LUBUNTU (ver: 20.04) machine via Universal Serial Bus (USB) Port<br/>
<br/>
<b>Answer:</b><br/>
1) LUBUNTU Main Menu -> Preferences -> Printers -> Server -> Settings...<br/>
--> Put CHECKMARK in CHECKBOX, "Publish shared printers connected to this system"<br/>
2) iPAD Tablet Computer -> Settings -> WiFi: Turn OFF, Turn ON<br/>
3) brother DCP-L2540DW Power: Turn OFF, Turn ON<br/>
<br/>
<b>3.3.2) Problem:</b> Windows7 Computer connected to network does NOT cause Printer to print<br/>
Printer connected to LUBUNTU (ver: 20.04) machine via Universal Serial Bus (USB) Port<br/>
<br/>
<b>Answer:</b><br/>
<img src="https://github.com/usbong/KMS/blob/master/Notes/res/noteSambaPrintServerWindows7PCToLUBUNTU20Dot04LTSPCSharedNetworkV20220309T1102.jpg" width="30%"><br/>
1) Enter the following COMMAND in LUBUNTU's Terminal Window:<br/>
<b>sudo apt install samba</b><br/>
<br/>
--> If installation FAILS due to dependencies, enter:<br/> 
<b>sudo apt-get install aptitude</b><br/>
<b>sudo aptitude install samba</b><br/>
<br/>
2) edit <b>/etc/samba/smb.conf</b><br/>
<br/>
--> In the [printers] section, CHANGE the following to "yes":<br/>
<b>browsable = yes</b><br/>
<b>guest ok = yes</b><br/>
<br/>
3) Enter the following COMMANDs in LUBUNTU's Terminal Window:<br/>
<b>sudo systemctl restart smbd.service</b><br/>
<b>sudo systemctl restart nmbd.service</b><br/>

### References
3.3.R.1) https://ubuntu.com/server/docs/samba-print-server; last accessed: 20220309<br/>
3.3.R.2) https://support.brother.com/g/b/downloadtop.aspx?c=ph&lang=en&prod=dcpl2540dw_us_as; last accessed: 20220309<br/>
