GNU Make 에서 필요한 내용을 추려보았다.
(https://www.gnu.org/software/make/manual/html_node/)

- Rule
  - 형태
```
targets : prerequisites ; recipe
    recipe
        …
```
  - meaning: prerequirites 가 targets 보다 recent 하면 recipe 들을 수행하라
  
  - target
    - file name
    - ```all``` 같이 일반적 명칭도 쓴다. --> phony target 이라고 부름
    - prerequisite 은 file name
  - Running make
    - ```$ make``` 라고만 치면 첫번째 타겟 (. 으로 시작하지 않는)을 실행 (default target)
    
- Directive
  - makefile 내에서 쓰이는 명령어.
  - 예: ```include ```
    - ```include ../*.mk $(DEFAULT_INCLUDE_FILE)``` 이런 식으로 쓸 수 있음.
    - 파일 찾는 순서: 현재 디렉토리, ```-I```, ```--include-dir``` option에 명시된 dir 등
- make의 2 phase 동작
  - 1st phase: 모든 makefile을 읽어서 (include된 것들) 변수 초기화, dependency graph 생성
    - ```$(변수)```는 이 때 변수의 내용으로 치환
    - ```$$(변수)```는 ```$(변수)```로 치환, 이후 2nd phase에서 변수의 내용으로 치환됨
  - 2nd phase: 실행될 target 을 위한 rule 들을 실행
  

