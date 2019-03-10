## Here Document
grammar : ` << EOF_STR ... EOF_STR`

```shell
volumio@rabbit-music-player:~/study$ tr aaa bbb << EOF
> aaa bbb ccc ddd aaa bbb
> EOF
bbb bbb ccc ddd bbb bbb
```

## `test`
```shell
volumio@rabbit-music-player:~$ test 1 -eq 2 && echo $C
1
volumio@rabbit-music-player:~$ test  abcd == efef && echo $C
1
volumio@rabbit-music-player:~$ test  abcd == abcd && echo $C
0
volumio@rabbit-music-player:~$ test -e .bashrc && echo $C
0
volumio@rabbit-music-player:~$ test -e .bashrc_not_exist && echo $?
```

## `1>/dev/null`, `2>/dev/null`
```shell
volumio@rabbit-music-player:~$ ls
myCloud  myCloudMout.howto
volumio@rabbit-music-player:~$ ls  1>/dev/null
volumio@rabbit-music-player:~$

volumio@rabbit-music-player:~$ ls not_exist
ls: cannot access not_exist: No such file or directory
volumio@rabbit-music-player:~$ ls not_exist 2>/dev/null
volumio@rabbit-music-player:~$
```

## _$(command)_ : Command substitution
```shell
$ COUNT=$(grep -c "br" index.html)
$ echo $COUNT
1
$ COUNT=`grep -c "br" index.html`
$ echo $COUNT
1
$ echo "This machine is $(hostname) on $(date)"
This machine is rabbit-music-player on Sat Mar  9 12:52:51 UTC 2019
```

## Creating an empty file
```shell
volumio@rabbit-music-player:~/study$ cat /dev/null > empty.1
volumio@rabbit-music-player:~/study$ cp /dev/null empty.2
volumio@rabbit-music-player:~/study$ : > empty.3
volumio@rabbit-music-player:~/study$ touch empty.4

volumio@rabbit-music-player:~/study$ ll empty.*
-rw-r--r-- 1 volumio volumio 0 Mar 10 06:31 empty.1
-rw-r--r-- 1 volumio volumio 0 Mar 10 06:31 empty.2
-rw-r--r-- 1 volumio volumio 0 Mar 10 06:31 empty.3
-rw-r--r-- 1 volumio volumio 0 Mar 10 06:33 empty.4
```

## dir name and file name
```shell
volumio@rabbit-music-player:~/study$ FN=$(pwd)/$(ls test.log) ; echo "$(dirname $FN) --> $(basename $FN)"
/home/volumio/study --> test.log
```

## sub-shell
A new shell is executed for `( .. )`.
When script is
```shell
volumio@rabbit-music-player:~/study$ cat sub-shell.sh
#!/bin/sh

VV=$(pwd)
echo "pwd = $VV. Goint to subshell. cd /"

(
  cd /
  VV=$(pwd)
  echo "(in subshell) pwd = $VV"
)

echo "pwd = $VV"
```

output is

```shell
volumio@rabbit-music-player:~/study$ ./sub-shell.sh
pwd = /home/volumio/study. Goint to subshell. cd /
(in subshell) pwd = /
pwd = /home/volumio/study
```

## `find`
- `find -type f` and `find -type d`
- `find -ls`

```
volumio@rabbit-music-player:~/study$ find /usr/lib -type f -print | wc -l
5141
volumio@rabbit-music-player:~/study$ find /usr/lib -type d -print | wc -l
497
volumio@rabbit-music-player:~/study$ find /usr/lib -type f -name "libc*.so" -ls
 15332    6 -rw-r--r--   1 root     root         5452 Mar 29  2018 /usr/lib/i386-linux-gnu/openssl-1.0.0/engines/libcapi.so
 15333   23 -rw-r--r--   1 root     root        22832 Mar 29  2018 /usr/lib/i386-linux-gnu/openssl-1.0.0/engines/libchil.so
 15334   23 -rw-r--r--   1 root     root        22696 Mar 29  2018 /usr/lib/i386-linux-gnu/openssl-1.0.0/engines/libcswift.so
```

- `find -exec cmd .. {} ..`
  - use `\;` to run cmd for each item found
  - use `+` to run cmd for whole items

```
gnu/openssl-1.0.0/engines/libcswift.so
volumio@rabbit-music-player:~/study$ find /usr/lib -type f -name "libc*.so" -exec echo '{}' \;
/usr/lib/i386-linux-gnu/openssl-1.0.0/engines/libcapi.so
/usr/lib/i386-linux-gnu/openssl-1.0.0/engines/libchil.so
/usr/lib/i386-linux-gnu/openssl-1.0.0/engines/libcswift.so

volumio@rabbit-music-player:~/study$ find /usr/lib -type f -name "libc*.so" -exec echo '{}' +
/usr/lib/i386-linux-gnu/openssl-1.0.0/engines/libcapi.so /usr/lib/i386-linux-gnu/openssl-1.0.0/engines/libchil.so /usr/lib/i386-linux-```



