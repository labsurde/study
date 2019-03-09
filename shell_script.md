
## test
```
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

## 1>/dev/null, 2>/dev/null
```
volumio@rabbit-music-player:~$ ls
myCloud  myCloudMout.howto
volumio@rabbit-music-player:~$ ls  1>/dev/null
volumio@rabbit-music-player:~$

volumio@rabbit-music-player:~$ ls not_exist
ls: cannot access not_exist: No such file or directory
volumio@rabbit-music-player:~$ ls not_exist 2>/dev/null
volumio@rabbit-music-player:~$
```

### _$(command)_ : Command substitution
```
$ COUNT=$(grep -c "br" index.html)
$ echo $COUNT
1
$ COUNT=`grep -c "br" index.html`
$ echo $COUNT
1
$ echo "This machine is $(hostname) on $(date)"
This machine is rabbit-music-player on Sat Mar  9 12:52:51 UTC 2019
```
