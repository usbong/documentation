# How to Remove SSL (Secure Sockets Layer)

1) execute: <b>sudo a2dismod ssl</b>

2) update: <b>/etc/apache2/apache2.conf</b><br>
--> comment out: <b>SSLEngine on</b><br>
--> comment out: <b>SSLProtocol all</b><br>
--> comment out: <b>SSLCertificateFile your_SSLCertificatePublic.crt</b><br>
--> comment out: <b>SSLCertificateKeyFile your_SSLCertificatePrivate.key</b><br>
--> comment out: <b>SSLCertificateChainFile your_SSLCertificateChain.crt</b><br>

3) execute: <b>sudo apachectl restart</b>

4) update: <b>.../application/config/config.php</b><br>
--> remove: "<b>https</b>", i.e. "<b>$config['base_url'] = 'http://your_website.ph/';</b>"<br>
--> note: CodeIgniter Web Framework

5) update: <b>.../.htaccess</b><br>
--> comment out: <b>RewriteCond %{HTTPS} !=on</b><br>
--> comment out: <b>RewriteRule ^/?(.*) https://%{SERVER_NAME}/$1 [R,L]</b>
