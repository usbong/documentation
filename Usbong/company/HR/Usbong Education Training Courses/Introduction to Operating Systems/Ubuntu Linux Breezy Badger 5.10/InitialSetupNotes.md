# Ubuntu Linux Breezy Badger 5.10
# Initial Setup Notes: Action Steps

## 1) Update Sources List using the "gedit" Text Editor Tool
<b>Filename and location:</b> /etc/apt/[sources.list](https://github.com/usbong/documentation/blob/master/Usbong/hardware%20software%20integration/Operating%20System%20(OS)/res/Ubuntu%20Linux%20Breezy%20Badger%205.10/sources.list)
## 2) Write and execute the following commands in the Terminal Window
<b>sudo apt-get update</b><br/>
<b>sudo apt-get upgrade</b><br/>
<b>sudo apt-get install --reinstall build-essential</b><br/>
<b>sudo apt-get install free-java-sdk</b><br/>
## 3) Copy and paste the "Usbong Training" folder onto the Desktop

## 4) Install XAMPP
### 4.1) Download XAMPP version 1.6 for Linux
<b>Filename:</b> xampp-linux-1.6.tar.gz<br/>
<b>Location:</b> https://sourceforge.net/projects/xampp/files/XAMPP%20Linux/1.6/;<br/>
last accessed: 20200715
### 4.2) Extract zipped folder of the XAMPP version 1.6 for Linux
4.2.1) Right click using the computer mouse the downloaded zipped folder<br/>
4.2.2) Choose "Extract Here"<br/>
<b>Output:</b>
"lampp" folder
### 4.3) Write and execute the following commands in the Terminal Window
<b>sudo cp -r lampp /opt/</b><br/>
<b>cd /opt</b><br/>
<b>sudo chmod -R 777 lampp</b><br/>

#### Reminder:
Your current directory in the Terminal Window should be where you extracted the zipped folder.

### 4.4) Start XAMPP: Write and execute the following commands in the Terminal Window
<b>cd /opt/lampp</b><br/>
<b>sudo ./lampp start</b><br/>
### 4.5) Set XAMPP Security: Write and execute the following commands in the Terminal Window
<b>cd /opt/lampp</b><br/>
<b>sudo ./lampp security</b><br/>
### 4.6) Verify XAMPP commands: Write and execute the following commands in the Terminal Window
<b>cd /opt/lampp</b><br/>
<b>sudo ./lampp --help</b><br/>

## 5) Install CodeIgniter Framework for use with PHP Computer Language
### 5.1) Download CodeIgniter version 2.2.6
<b>Filename:</b> CodeIgniter-2.2.6.zip<br/>
<b>Location:</b> https://codeigniter.com/download;<br/>
last accessed: 20200715
### 5.2) Extract zipped folder of the CodeIgniter version 2.2.6
5.2.1) Right click using the computer mouse the downloaded zipped folder<br/>
5.2.2) Choose "Extract Here"<br/>
<b>Output:</b>
"CodeIgniter-2.2.6" folder
### 5.3) Rename extracted output folder from "CodeIgniter-2.2.6" to "usbong"
5.3.1) Right click using the computer mouse the downloaded zipped folder<br/>
5.3.2) Choose "Rename..."<br/>
<b>Output:</b>
"usbong" folder
### 5.4) Write and execute the following commands in the Terminal Window
<b>sudo cp -r usbong /opt/lampp/htdocs/</b><br/>
<b>cd /opt/lampp/htdocs/</b><br/>

#### Reminder:
Your current directory in the Terminal Window should be where you extracted the zipped folder.

### 5.5) Verify "Welcome to CodeIgniter!" web page using the following Computer Web Address in the Web Browser
<b>Web Address:</b> http://localhost/usbong<br/>

#### Reminder:
Remember to execute "Start XAMPP" in Action Step 4.4.

# Additional Notes: Unix Commands
## 1) Copy a directory and all its sub-folders
<b>sudo cp -r \<start directory> \<destination directory></b>
<br/><br/>
<b>Reminder:</b><br/>
"r" in "-r" is a small letter

## 2) Change a directory and all its sub-folders to be read, write, and executable for all users
<b>sudo chmod -R 777 \<directory></b>
<br/><br/>
<b>Reminder:</b><br/>
"R" in "-R" should be a capital letter

## 3) Remove a directory and all its sub-folders
<b>sudo rm -rf \<directory></b>

# References:
1) https://askubuntu.com/questions/217893/how-to-delete-a-non-empty-directory-in-terminal;<br/>
last accessed: 20200714
2) https://askubuntu.com/questions/904599/install-xampp-on-ubuntu-16-04;<br/>
last accessed: 20200714
3) https://askubuntu.com/questions/890818/ubuntu-16-04-how-to-start-xampp-control-panel;<br/>
last accessed: 20200714
