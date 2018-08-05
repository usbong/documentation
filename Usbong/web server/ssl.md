How to Remove SSL (Secure Sockets Layer)

1) execute: sudo a2dismod ssl

2) update: /etc/apache2/apache2.conf
--> comment out: SSLEngine on
--> comment out: SSLProtocol all
--> comment out: SSLCertificateFile your_SSLCertificatePublic.crt
--> comment out: SSLCertificateKeyFile your_SSLCertificatePrivate.key
--> comment out: SSLCertificateChainFile your_SSLCertificateChain.crt

3) execute: sudo apachectl restart

4) update: .../application/config/config.php
--> remove: "https", i.e. "$config['base_url'] = 'http://your_website.ph/';"
--> note: CodeIgniter Web Framework

5) update: .../.htaccess
--> comment out: RewriteCond %{HTTPS} !=on
--> comment out: RewriteRule ^/?(.*) https://%{SERVER_NAME}/$1 [R,L]