# Miscellaneous Commands
## I. Linux-based Server
1) Change the owner of "all files in the directory" to usbong.</br></br>
<b>sudo chown usbong *</b></br></br>
--> Instead of *, you can specify the name of the file, e.g. style.php.</br></br>
<b>sudo chown usbong style.php</b>

2) Change the group of "all files in the directory" to usbong.</br></br>
<b>sudo chgrp usbong *</b></br></br>
--> Instead of *, you can specify the name of the file, e.g. style.php.</br></br>
<b>sudo chgrp usbong style.php</b>

3) Change the group of "all files in the directory" to be writable.</br></br>
<b>chmod g+w *</b></br></br>
--> Instead of *, you can specify the name of the file, e.g. style.php.</br></br>
<b>chmod g+w style.php</b>

## II. Windows-based Server
### 1) Make the Windows-based Server sleep using Command Prompt.</br></br>
<b>rundll32.exe powrprof.dll,SetSuspendState Sleep</b></br></br>
--> You can save the aforementioned command as "sleep.bat" on Notepad.</br>
--> Make sure to include the quotation marks so that it saves as a ".bat" or batch file, instead of ".bat.txt".</br>
#### You can use Window's "Task Scheduler" to automate this task.
--> You may want to do this if your server is in a local network and the office/clinic that uses it is closed in the evening.</br>
--> This should save the company from unnecessary electricity consumption.</br>
--> In addition, this should strengthen server security by making it difficult for unauthorized people from accessing the server.</br>
1) In the "Task Scheduler" Window, click the "Task Scheduler Library" folder on the left panel.</br>
2) In the "Task Scheduler" Window, click "Create Task..." on the "Actions" panel on your right.</br>
3) In the "Create Task" Window, inside the "General" tab, write the name of the task, e.g. "Usbong Auto-sleep PC" for the "Name:" field.</br>
4) In the "Create Task" Window, inside the "Triggers" tab, click "New...".</br>
5) In the "New Trigger" Window, choose when and what time you'd want the task to start, e.g. Daily, starting today, at 8:30:00 PM.</br>
6) In the "New Trigger" Window, click the "OK" button.</br>
7) In the "Create Task" Window, inside the "Actions" tab, click "New...".</br>
8) In the "New Action" Window, click "Browser" and choose the "sleep.bat" file for the "Program/script:" field.</br>
9) In the "New Action" Window, click the "OK" button.</br>
10) In the "Create Task" Window, click the "OK" button.</br>
Done!</br>
</br>
### 2) Make the Windows-based Server wake up using Command Prompt.</br></br>
<b>exit</b></br></br>
--> You can save the aforementioned command as "wake.bat" on Notepad.</br>
--> Make sure to include the quotation marks so that it saves as a ".bat" or batch file, instead of ".bat.txt".</br>
#### You can use Window's "Task Scheduler" to automate this task.
--> You may want to do this if your server is in a local network and the office/clinic that uses it is closed in the evening.</br>
--> This should save the company from unnecessary electricity consumption.</br>
--> In addition, this should strengthen server security by making it difficult for unauthorized people from accessing the server.</br>
1) Using an Administrator account, in the "Task Scheduler" Window, click the "Task Scheduler Library" folder on the left panel.</br>
2) In the "Task Scheduler" Window, click "Create Task..." on the "Actions" panel on your right.</br>
3) In the "Create Task" Window, inside the "General" tab, write the name of the task, e.g. "Usbong Auto-wake PC" for the "Name:" field.</br>
4) In the "Create Task" Window, inside the "Triggers" tab, click "New...".</br>
5) In the "New Trigger" Window, choose when and what time you'd want the task to start, e.g. Daily, starting today, at 8:00:00 AM.</br>
6) In the "New Trigger" Window, click the "OK" button.</br>
7) In the "Create Task" Window, inside the "Actions" tab, click "New...".</br>
8) In the "New Action" Window, click "Browser" and choose the "wake.bat" file for the "Program/script:" field.</br>
9) In the "New Action" Window, click the "OK" button.</br>
10) In the "Conditions" Window, click to add a check in the checkbox for "Wake the computer to run this task."</br>
11) In the "General" Window, click to select "Run whether the user is logged on or not."</br>
12) In the "General" Window, click to add a check in the checkbox for "Do not store password. The task will only have access to local computer resources."</br>
13) In the "General" Window, click to add a check in the checkbox for "Run with highest privileges."</br>
14) In the "Create Task" Window, click the "OK" button.</br>
Done!



