$ssh_enable = <<SCRIPT
sudo apt-get update
sudo apt-get -y upgrade
sudo apt-get install -y expect
sudo sed -i 's/prohibit-password/yes/' /etc/ssh/sshd_config
sudo sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config
sudo service sshd restart
echo '#!/usr/bin/expect
set timeout 20
spawn sudo passwd root
expect "Enter new UNIX password:" {send "root\\r"}
expect "Retype new UNIX password:" {send "root\\r"}
interact' > change_password
chmod +x change_password
./change_password
SCRIPT

$install_package = <<SCRIPT
sudo apt-get update
sudo apt-get -y upgrade
sudo apt-get -y install python3-pip
sudo apt-get -y install sshpass
sudo apt-get -y install python-dev python3-dev 
sudo apt-get -y install libssl-dev libffi-dev libxml2-dev libxslt1-dev zlib1g-dev
sudo pip3 install --upgrade setuptools
sudo pip3 install Fabric==1.14.0
sudo pip3 install Fabric3
sudo pip3 install ansible==2.4.2.0
SCRIPT

Vagrant.configure(2) do |config|
  config.vm.define 'main' do |main|
    main.vm.hostname = 'main'
    main.vm.box = 'ubuntu/xenial64'
    main.vm.network 'private_network', ip: '10.0.0.100'
    main.vm.synced_folder 'ops/', '/srv/ops'
    main.vm.provision 'shell', inline: $install_package
  end

  config.vm.define 'server1' do |server1|
    server1.vm.hostname = 'server1'
    server1.vm.box = 'ubuntu/xenial64'
    server1.vm.network :forwarded_port, guest: 5000, host: 8001, id: 'http'
    server1.vm.network 'private_network', ip: '172.16.200.101'
    server1.vm.provision 'shell', inline: $ssh_enable
  end

  config.vm.define 'server2' do |server2|
    server2.vm.hostname = 'server2'
    server2.vm.box = 'ubuntu/xenial64'
    server2.vm.network :forwarded_port, guest: 5000, host: 8002, id: 'http'
    server2.vm.network 'private_network', ip: '172.16.200.102'
    server2.vm.provision 'shell', inline: $ssh_enable
  end
end
