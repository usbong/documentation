# Database Technologies: MySQL Commands List
<b>Note:</b> You can execute the MySQL commands in both Linux and Windows machines.

# 1) Use the following commands in the Terminal Window
## 1.1) Access MySQL
mysql -u\<username> -p

## 1.2) Import into an existing database a SQL file with list of commands
mysql -u\<username> -p <database_name> < <file.sql>

## 1.3) Export an existing database into a SQL file with list of commands
mysqldump -u\<username> -p <database_name> > <outputFile.sql>

# 2) Use the following commands in the MySQL Window
## 2.1) Show existing databases
show databases;

## 2.2) Use an existing database
use \<database name>;

## 2.3) Show tables in the current database that you are using
show tables;

## 2.4) Browse all available content from a table in the current database that you are using
select * from \<table name>;

## 2.5) Create new database
create database \<database_name>;

## 2.6) Destroy existing database
drop database \<database_name>;

## 2.7) Quit using MySQL Window
quit;

# 3) Recommended Reading:
1) https://www.mysql.com/; last accessed: 20200729
