## setup raspberry pi 3b+ for mpd + upmpdcli

### image
https://downloads.raspberrypi.org/raspbian_full/images/raspbian_full-2019-04-09/2019-04-08-raspbian-stretch-full.zip

- lite 버젼은 뭔가 잘 안됨 (설치되나 인식안됨)
- buster 버젼은 upmpdcli 설치방법이 아직 없음

### setting 1
```
부팅 후 국가선택
시스템 자동 업데이트 후 리부팅
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

### setting 2
```
시스템 메뉴의 라즈베리 파이 설정 들어가서 부팅을 desktop 에서 CLI로 바꿈
리부트
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
sudo nano /etc/apt/sources.list.d/upmpdcli.list

아래 두줄 입력
deb http://www.lesbonscomptes.com/upmpdcli/downloads/raspbian/ stretch main
deb-src http://www.lesbonscomptes.com/upmpdcli/downloads/raspbian/ stretch main
control-X -> Y -> Enter

sudo apt-get update
sudo apt-get install upmpdcli
sudo apt-get install upmpdcli-tidal
```

## 문제점 해결
### BubbleUPnP 에서는 보여지고 Play도 되는데 소리가 안난다.
- `aplay -l`을 실행해본다. 나의 경우는 아래와 같았다. USB Audio가 `Card 1: .. device 0: ...` 이라고 되어 있다. 이 경우 mpd의 설정파일에 `hw:1,0`이라고 되어 있어야 한다.

```
# aplay -1
card 0: ALSA [bcm2835 ALSA], device 1: bcm2835 IEC958/HDMI [bcm2835 IEC958/HDMI]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 1: X20 [XMOS USB Audio 2.0], device 0: USB Audio [USB Audio]
  Subdevices: 0/1
  Subdevice #0: subdevice #0
```

- mpd.conf 수정
```
$ sudo nano /etc/mpd.conf

아래 부분을 찾아서 device 부분을 아래처럼 고친다.

audio_output {
        type            "alsa"
        name            "My ALSA Device"
        device          "hw:1,0"        # 이 부분을 hw:1,0 으로 해주면 됨
 
```

- 수정 후 mpd 다시 시작
```
 $ systemctl restart mpd
```
