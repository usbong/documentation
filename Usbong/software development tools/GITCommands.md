# GIT Commands
Operating System (OS): Linux, macOS, Unix-like Systems

## 1) Start: Download Repository from the Network
Example: sudo git clone https://github.com/usbong/documentation.git

## 2) Verify: Local Repository 
--> If not updated, download only the files auto-identified to have been updated.<br/>
Example: sudo git pull https://github.com/usbong/documentation.git

## 3) Update: Local Files
### 3.1) Create copy of newest version before updating the file, e.g. OpenGLCanvas.cpp
Example: cp OpenGLCanvas.cpp OpenGLCanvas.cppV20210608T0605

### 3.2) Edit the file using Text Editor Tool, e.g. XCode, Notepad++, Featherpad<br/>
Example: xed OpenGLCanvas.cpp

## 4) Upload: Updated Local File to Repository on the Network
### 4.1) Add file in list to upload<br/>
Example: sudo git add OpenGLCanvas.cpp

### 4.2) Commit the list to upload, with added note to identify
Example: sudo git commit -m "added: verify set to reset when outside window"

### 4.3) Push the list to upload to Repository on the Network
Example: sudo git push https://github.com/usbong/documentation.git

#### Additional Notes:
#### 4.3.1) Update username and email address of author
Example:<br/>
sudo config -global user.name “halimbawa”<br/>
sudo git config --global user.email “halimbawa@usbong.ph<br/>
sudo git commit --amend --reset-author<br/>

### Reference:
https://stackoverflow.com/questions/11961600/fatal-not-a-git-repository-or-any-of-the-parent-directories-from-git-status;<br/>
last accessed: 20210607<br/>
answer by:  Umit Kaya, 20161219T0344<br/>
