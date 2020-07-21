# Database System: Notes
## I. Debian/Ubuntu Linux Operating System (OS)
<b>OS version:</b> Linux Debian 2.6.34.9<br/>
<b>MySQL version:</b> 5.1.49-3

## II. MySQL: How to reset password?
## 1 Stop the MySQL server by using the following command:
<b>shell> kill \`cat /mysql-data-directory/host_name.pid`</b>

where: "mysql-data-directory" = "/var/run/mysqld"<br/>
where: "host_name.pid" = "mysqld.pid"

### Note:
The "mysql-data-directory" location may vary.
Here are the common locations:<br/><br/>
/var/lib/mysql/<br/>
/var/run/mysqld/<br/>
/usr/local/mysql/data/<br/>

## 2) Create a new text file containing the following command:
<b>SET PASSWORD FOR 'root'@'localhost' = PASSWORD('myPass');</b>

## 3) Save the file as "mysql-init" in the "/home" directory
<b>Output:</b> home/mysql-init

## 4) Start the MySQL server by using the following command:
<b>shell> mysqld --init-file=/home/me/mysql-init &</b>

### Reminder:
1) Verify that there are no mysql processes already running before you start the MySQL server.
#### Useful commands:
1.1) Show all running processes in a list.<br/>
<b>ps ax</b><br/>
1.2) Show all running processes in a list with the keyword, "mysql".<br/>
<b>ps ax | grep mysql</b><br/>
1.3) Destroy a specific process.<br/>
<b>kill -9 \<processId>

## References:
1) https://dev.mysql.com/doc/refman/8.0/en/resetting-permissions.html;<br/>
last accessed: 20200720<br/>
2) https://stackoverflow.com/questions/7534056/mysql-root-password-change;<br/>
last accessed: 20200720

## III. Problem & Answer
## Problem: Cannot login to phpmyadmin
<b>Sample Web Address:</b> http://192.168.11.65/phpmyadmin
## Answer: 
### 1) Go to /etc/phpmyadmin
### 2) Edit using a text-editor config.inc.php
### 3) Add the following rows:
$cfg['Servers'][$i]['user']          = 'root';<br/>
$cfg['Servers'][$i]['password']      = 'myPass'; // use here your password<br/>
$cfg['Servers'][$i]['auth_type']     = 'config';<br/>

### Reminder:
1) No need to restart the Apache web server.

### Reference:
1) phpMyAdmin 3.3.7 Documentation 
