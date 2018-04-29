Excerpted from [GNU Make](https://www.gnu.org/software/make/manual/html_node/)

- Rule
    ```
    targets : prerequisites ; recipe
        recipe
        …
    ```
  - mearning : if prerequirites is more recent than targets, run recipes
  - target
    - file name
    - name, i.e., ```all``` --> called *phony target*
    - prerequisite is file names
  - Running make
    - ```$ make``` runs the first target (not stating from ```.``` --> *default target*
- Directive
  - predefined instruction in makefile
    - i.e.,: ```include ```
      - usage : ```include *.mk $(DEFAULT_INCLUDE_FILE)```
    - searching order
      - current directory
      - ```-I```, ```--include-dir``` option에 명시된 dir 등
- make performs 2 phase-action
  - 1st phase
    - read all makefiles included by ```include```
    - initialize variables
    - build dependency graph
    - ```$(var)``` is substituted by *value* of var
    - ```$$(var)``` is substituted by ```$(var)```
      - 2nd phase에서 변수의 내용으로 치환됨
    - 2nd phase: 실행될 target 을 위한 rule 들을 실행

- Filename wildcard
  - ```objects = *.o``` 인  경우```$(objects)``` 는 string ```*.o``` 를 뜻함
  - recipe에 사용되는 ```$(objects)``` 는 string ```*.o``` 를 뜻함. 실제 expansion은 sh 에 의해 일어남.
  - 굳이 expansion 하고 싶으면 ```objects := $(wildcard *.o)``` 라고 하면 됨
  - ``` build: $(objects)``` 라고 prerequisite 에 사용하면 실제 파일이름으로 expansion됨
 
- directory search
    - how can make finds files?
        - first, search current directory
        - ```VPATH ``` 변수
            - make는 현재 디렉토리에 파일이 없으면 ```VPATH``` 에 정의된 디렉토리들을 찾음.
            - ```VPATH = src:../headers```
        - ```vpath``` directive
            - ```vpath %.h ../headers:../include```
            -h 파일은 ```../headers```에서, 그 다음에 ```../include```에서 찾아라
    - lib 파일도 위의 두개에서 찾음
        - lib file은 ```lib%.so``` 의 패턴
        - 아래 예는 libcurses.so 파일을 위의 방법대로 찾게 됨
            ```
            foo : foo.c -lcurses
                cc $^ -o $@
            ```        
- Phony target        
    - 아래는 ```rm```이 ```clean``` 이라는 file을 만들지 않으므로, make는 ```clean```파일이 없다고 판단하여 항상 ```rm```을 실행하게 됨
    ```
    clean:
        rm *.o temp
    ```
    - 그런데 만일 ```clean```이라는 파일이 있으면 위 target의 recipe가 실행되지 않음.
        - 이럴 때는 ```.PHONY``` 로 명시적으로 phony target임을 알려야 함.
        ```
        .PHONY: clean
        clean:
            rm *.o temp
        ```
- prerequisite이나 recipe가 없는 rule
    - target이 항상 update 되었다고 처리함
    - 아래에서 FORCE는 항상 새로 업데이트된다고 처리되므로 clean이 항상 불리워지게 됨 (설령 ```clean```이라는 파일이 존재해도)
    ```
    clean: FORCE
        rm $(objects)
    FORCE:    
    ```

- multiple targets in a rule
  - same with separate rules with same pre-requisite or recipe
    '''
    kbd.o command.o files.o: command.h
    '''    

- recipe의 변수는 치환되어 shell 에 호출되기 위해 넘겨짐
    - 아래의 recipe는 ```$(LIST)``` 는 value로 바뀌고 ```$$i```는 ```$i``` 스트링으로 바뀌어 shell 에게 호출됨 (```$``` 문자는 recipe 에서 ```$$``` 로 써야함)
    ```
    LIST = one two three
    all:
        for i in $(LIST); do \
            echo $$i; \
        done
    ```    
    - shell로 넘겨지는 스트링
    ```
    for i in one two three; do \
        echo $i; \
    done
    ```
- recipe 는 shell로 보내지기 전에 한번 프린트됨. 프린트하기 싫으면 ```@```를 붙이면 됨.
    - ```$ make -n``` or ```$ make --just-print```는 recipe를 실행하지 않고 프린트만 함.
    - ```-s```, ```--silent```는 프린트 안하고 실행함
- recipe 실행
    - 라인마다 sh이 새로 실행되어 넘겨짐. 따라서, 아래 실행시, /Product/temp는 만들어지지 않음 (현재디렉토리에 temp를 만듦)
    ```
    INSTALL:
        cd /Product
        mkdir temp
    ```
    - 한 rule의 recipe에 걸쳐 shell 을 하나만 쓰려면 ```.ONESHELL```을 호출하면 됨
    ```
    .ONESHELL:
    foo : bar/lose
        cd $(@D)
        gobble $(@F) > ../$@
    ```
      - 이 경우 첫줄 첫 글자 ```@```는 프린트하지 말라는 의미로 해석됨.
    - shell은 기본적으로 ```/bin/sh```가 실행됨.
      - 다른 shell을 호출하려면 아래처럼 하면 됨. ```.SHELLFLAGS```는 shell 호출시 넘겨주는 인자
        ```
        .ONESHELL:
        SHELL = /usr/bin/perl
        .SHELLFLAGS = -e
        show :
            my @f = qw(a b c);
            print "@f\n";
        ```
    - recipe 실행시 에러나면 make가 멈추게 됨. ```-```를 붙이면 에러나도 그냥 지나감.
    ```
    clean:
        -rm -f *.o
    ```
    - recursive make (makefile 에서 make를 다시 호출하는 것)
        ```
        subsystem:
            cd subdir && $(MAKE)
        ```
        - ```$(MAKE)```는 make의 절대경로로 치환됨
        - 호출된 make는 호출한 make의 variable을 모름. 전달하려면```export``` 해줄 수 있음.
        ```
        export MY_EMAIL
        ```
        ```
        export MY_EMAIL = abc@def.com
        ```
        ```
        unexport MY_EMAIL
        ```
        - 모든 variable이 export 되어야 한다면. (```unexport``` 써서 제외할 변수들을 지정할 수는 있음)
        ```
        export 
        ```
        
        

    


