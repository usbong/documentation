# phpMyAdmin
If you access phpMyAdmin on your server online, you may not necessarily want it to be always open/accessible.<br>

To further increase security, you can disable it.<br>

### Note: 
The commands that I've written here are for Linux-based servers.

## Table of Contents
<h3>I. How to disable phpMyAdmin</h3>
<h3>II. How to enable phpMyAdmin</h3>
<br>

# I. How to disable phpMyAdmin
You can disable phpMyAdmin by disabling the module configuration.<br>
1) execute: <b>sudo a2disconf phpmyadmin.conf</b><br>
2) execute: <b>sudo /etc/init.d/apache2 restart</b><br>

# II. How to enable phpMyAdmin
You can enable phpMyAdmin by enabling the module configuration.<br>
1) execute: <b>sudo a2enconf phpmyadmin.conf</b><br>
2) execute: <b>sudo /etc/init.d/apache2 restart</b><br>
