# Unix Commands
For use with the following select Operating Systems: 
1) Ubuntu Linux<br/>
2) macOS <br/>

## 1) Change directory
<b>cd \<directory></b><br/>
### Examples: 
1) <b>cd /home</b><br/>
2) <b>cd /home/unit_member</b><br/>
3) <b>cd usbong</b><br/>
4) <b>cd usbong/training</b>

### Reminders:
1) In examples 3 and 4, we do not add "/" before the directory due to the "usbong" folder already exists in the current directory.<br/>
2) In examples 1 and 2, we add a "/" before the directory to identify the location regardless of the current directory.<br/>

## 2) Change directory to the parent directory
<b>cd ..</b><br/>

### Example:
<b>cd /home/unit_member</b><br/>
<b>cd ..</b><br/>

### Output:
Current directory: <b>/home</b>

## 3) List the files inside the current directory
<b>ls</b><br/>

### Reminders:
1) We write "L" and "S" as small letters, i.e. "l" and "s"<br/>
2) We can add "-l" in the command to be "ls -l" for the computer to list the files with the details

## 4) Extract a zipped file
<b>tar -xvzf halimbawa.tar.gz</b><br/>
<br/>
<b>where:</b><br/>
<b>x</b> = extract<br/>
<b>v</b> = writes as output a list of files processed by the computer<br/>
<b>z</b> = use gzip tool due to file compressed as ".gz" zipped file using gzip<br/>
<b>f</b> = use the following filename, i.e. "halimbawa.tar.gz" 

### Notes:
1) tar = tar archiving utility<br/>
--> stores and extracts files from a tape or disk archive

### References:
1) http://linuxcommand.org/lc3_man_pages/tar1.html<br/>
last accessed: 20200805
2) https://askubuntu.com/questions/25347/what-command-do-i-need-to-unzip-extract-a-tar-gz-file
last accessed: 20200805<br/>
answer by: djeikyb, 20110208T2257<br/>
edited by: damadam, 20191129T1033
