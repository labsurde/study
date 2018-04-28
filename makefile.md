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
    


