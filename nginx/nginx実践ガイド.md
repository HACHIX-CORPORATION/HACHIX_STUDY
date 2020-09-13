# 概要
1. 名前：nginx (engine x: エンジンエックス)
2. 役割
    - Web Server
    - ロードバランサ
    - リバースプロキシ
3. 歴史
    - 2004: Igor Sysoev 
    - 2016: Apache, IIS (Internet Information Service), nginxは3強になっている。nginx: 30%

# Trouble Shootings
1. 413 Request Entity Too Large
    - default: 1MB
    - change client_max_body_size 
    - run command
        - sudo systemctl restart nginx
    - check status
        - sudo systemctl status nginx
        
        
2. Timeout Setting
    keepalive_timeout 600;
    send_timeout 180;
    proxy_connect_timeout 600;
    proxy_read_timeout    600;
    proxy_send_timeout    600;
        
    
    