# Table of Contents
<h3>Steps to use WinSCP to connect to your Linux server instance</h3>

1) Run <b>WinSCP.exe</b>

2) Under "Session", for the "File Protocol:" field, choose "SCP" in the dropdown menu.

3) For the "Host name:" field, write/enter as input your server's public address.<br>
--> The public address should be static; otherwise, you'll have to keep on updating this field whenever the public address changes.<br>
--> Note that depending on where you're hosting your server, its security settings may be set such that it can only accept incoming connections from certain addresses.

4) For the "Port number:" field, write/enter as input the port number your server uses to accept SSH connections.<br>
--> The default is "22".

5) For the "User name:" field, write/enter what you use to access/log into your server.

6) For the "Password:" field, write/enter the accompanying password for the user in step 5.

7) Click the "Advanced" button.

8) On the left panel, under SSH, click "Authentication".

9) In the "Private key file:" field, click "..." to select the PuTTY Private Key file, which is in ".ppk" format.

10) Click the "Login" button.
