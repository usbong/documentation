# Ubuntu Linux Breezy Badger 5.10
# Initial Setup Notes: Action Steps

## 1) Update Sources List using the "gedit" Text Editor Tool
Filename and location: /etc/apt/[sources.list](https://github.com/usbong/documentation/blob/master/Usbong/hardware%20software%20integration/Operating%20System%20(OS)/res/Ubuntu%20Linux%20Breezy%20Badger%205.10/sources.list)
## 2) Write and execute the following commands in the Terminal Window
<b>sudo apt-get update</b><br/>
<b>sudo apt-get upgrade</b><br/>
<b>sudo apt-get install --reinstall build-essential</b><br/>
<b>sudo apt-get install free-java-sdk</b><br/>
## 3) Copy and paste the "Usbong Training" folder onto the Desktop

TO-DO: -add: XAMPP installation

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
