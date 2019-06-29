## setup raspberry pi 3b+ for mpd + upmpdcli

### image
https://downloads.raspberrypi.org/raspbian_full/images/raspbian_full-2019-04-09/2019-04-08-raspbian-stretch-full.zip

- lite 버젼은 뭔가 잘 안됨 (설치되나 인식안됨)
- buster 버젼은 upmpdcli 설치방법이 아직 없음

### setting
```
passwd pi # 보안을 위해 암호 바꾸기
sudo apt-get update
sudo apt-get upgrade
```

### ssh 활성화 
```
sudo systemctl disable ssh.service
sudo systemctl enable ssh.service
sudo service ssh start
```

아래처럼 해도 된다고 함.
```
   $ cd /boot
   $ sudo touch ssh
   $ sudo reboot
```

### mpd
```
sudo apt-get install mpd
```

### upmpdcli

https://www.lesbonscomptes.com/upmpdcli/downloads.html 

#### key gen
```
sudo apt install dirmngr
gpg --keyserver pool.sks-keyservers.net --recv-key F8E3347256922A8AE767605B7808CE96D38B9201
```

#### 
```
sudo cat > /etc/apt/sources.list.d/upmpdcli.list
deb http://www.lesbonscomptes.com/upmpdcli/downloads/raspbian/ stretch main
deb-src http://www.lesbonscomptes.com/upmpdcli/downloads/raspbian/ stretch main

sudo apt-get install upmpdcli
sudo apt-get install upmpdcli-tidal
