# Printers and Scanners
## 1) Hewlett-Packard (HP) Deskjet Ink Advantage 2010 LINUX Drivers (Printer)
https://developers.hp.com/hp-linux-imaging-and-printing; last accessed: 20200620

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
### 2) Verify Command
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

### 3) Scan Command<br/>
<b>scanimage > outputImage.pnm</b><br/>
<br/>
where: ".pnm" is the image file format

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
<br/>
Done!<br/>
<br/>

### References:
1) https://bugs.launchpad.net/simple-scan/+bug/1539933; last accessed: 20200623<br/>
2) https://ubuntuforums.org/archive/index.php/t-2130330.html; last accessed: 20200623

