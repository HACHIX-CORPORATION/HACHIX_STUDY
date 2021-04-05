#Deploy EC手順
- 注意：
In Security Group check port 80 settings


1. Access into ubuntu 
`ssh -i "hachinenkin.pem" ubuntu@ec2-13-231-139-208.ap-northeast-1.compute.amazonaws.com`


2. Install Python 3.8
`sudo apt install python3.8`
`sudo apt install python3-pip`

3. Install NodeJS
  `sudo apt get update`  
  `curl -sL https://deb.nodesource.com/setup_10.x -o nodesource_setup.sh`  
  `bash nodesource_setup.sh`  
  `sudo apt-get install nodejs`  

4. Install nginx  
`sudo apt-get install nginx`  
`sudo ufw allow 'Nginx HTTP'`  
`sudo ufw allow 5000`  
`sudo ufw allow https`

- nginx config:
`nano /etc/nginx/sites-available/default`

       {
        listen 80 default_server;
        listen [::]:80 default_server;

        server_name_;

        root /var/www/example.com;
        index index.html;

        location / {
                # First attempt to serve request as file, then
                # as directory, then fall back to displaying a 404.
                # try_files $uri $uri/ =404;
                proxy_pass http://127.0.0.1:5000/;
                proxy_buffering off;
                
        }

* Start nginx: 
`sudo systemctl start nginx`
* Check nginx:
`sudo systemctl status nginx`

5. In <source_code>/Client/static  
`npm i`  
`npm run build`  
`npm i -g pm2`

6. Start app
On <source_code>/Server run:  
`python3 sever.py`   