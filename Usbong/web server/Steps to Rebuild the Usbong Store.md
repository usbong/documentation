# Steps to Rebuild the Usbong Store (Web Server)
## Prerequisites:
1) XAMPP software<br>
--> https://www.apachefriends.org/download.html; last accessed: 20180920<br>
--> version: 7.2.9 / PHP 7.2.9 (newest version at the time of writing)
2) Usbong Store .sql DB (newest version)<br>
--> https://github.com/usbong/UsbongStore/tree/master/db; last accessed: 20180920<br>
3) usbong_store folder from the Usbong Store GitHub repository<br>
--> https://github.com/usbong/UsbongStore; last accessed: 20180920

## Windows machine
1) Install XAMPP.
2) Open the XAMPP Control Panel.
3) Click Apache's "Stop" button using the XAMPP Control Panel.
4) Click Apache's "Start" button using the XAMPP Control Panel.
5) Open phpmyadmin by entering the following as the web browser address.<br>
http://localhost/phpmyadmin<br>
6) Create a new database or DB by clicking "New" on the left panel.
7) Enter "usbong_store" as the Database name.
8) Click "Create".
9) Click "Import" on the top tab.
10) Click "Browser...".
11) Select the Usbong Store .sql DB (newest version) file from your File Directory system.
12) Click the "Go" button at the bottom of the Import page.
13) Copy the "usbong_store" folder you downloaded from the Usbong Store GitHub repository.
14) Paste the "usbong_store" folder to "...xampp/htdocs/".

Done! You should now be able to access the following on your web browser.<br>
http://localhost/usbong_store<br>
### <b>Note:</b><br>
You can do the following if you want to modify the default port, i.e. 80, to another, e.g. 8080.

1) Open the XAMPP Control Panel.
2) Click Apache's "Config" button.
3) Click "Apache (httpd.conf)".
4) Update the following portion of the "httpd.conf" file.<br>
--> #<br>
--> # Listen: Allows you to bind Apache to specific IP addresses and/or<br>
--> # ports, instead of the default. See also the <VirtualHost><br>
--> # directive.<br>
--> #<br>
--> # Change this to Listen on specific IP addresses as shown below to<br>
--> # prevent Apache from glomming onto all bound IP addresses.<br>
--> #<br>
--> #Listen 12.34.56.78:80<br>
--> #Listen 80<br>
--> Listen 8080<br>
5) Save the "httpd.conf" file.
6) Close the "httpd.conf" file.
7) Click Apache's "Stop" button using the XAMPP Control Panel.
8) Click Apache's "Start" button using the XAMPP Control Panel.

Done!
