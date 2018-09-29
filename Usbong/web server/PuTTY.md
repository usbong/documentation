# Steps to use PuTTY to connect to your Linux server instance

1) Run <b>PuTTY.exe</b>.

2) For the "Host name:" field, write/enter as input your server's public address.<br>
--> The public address should be static; otherwise, you'll have to keep on updating this field whenever the public address changes.<br>
--> Note that depending on where you're hosting your server, its security settings may be set such that it can only accept incoming connections from certain addresses.<br>
--> You may also include the User name in the Host name field, e.g. usbong@webservices.ph.

4) For the "Port number:" field, write/enter as input the port number your server uses to accept SSH connections.<br>
--> The default is "22".

5) For the "Saved Sessions" field, write/enter as input the name of the session, so you can simply load it again when you access/log into your server.<br>
--> Otherwise, you'll have to redo the steps.

6) On the left panel, under "Category:", select Connection -> SSH -> Auth.<br>

7) In the "Private key field for authentication:" field, click "Browse..." to select the PuTTY Private Key file, which is in ".ppk" format.<br>

8) Click the "Open" button.<br>

Done! You should now be able to connect to your Linux server instance.
