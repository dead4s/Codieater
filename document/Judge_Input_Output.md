
# Judge Program input, output 

container에서 돌아가는 judge 프로그램을 사용하고 싶을때 참고할 수 잇는 문서입니다.   
judge 프로그램은 container내부에서 동작하며, 특정 코드를 컴파일, 실행하여 테스트케이스에 대한 결과를 파일로 작성해주는 프로그램을 말합니다.    
아래는 judge 프로그램이 들어있는 container에 input 주는 방법/ output을 받는 방법을 다룹니다.    

<br>
<br>

# $ Simple Example

사용할 docker image를 빌드합니다. 

```bash
git clone https://github.com/Codieater/Codieater.git
cd Codieater 
docker build -t codi_judge:3.0 -f docker/judge.dockerfile .
```
<br>

`/document/userCode`, `/document/testCase`에서 간단하게 테스트용으로 작성된 채점할 코드와 채점 데이터를 확인할 수 있습니다. 

```bash
document/
├── testCase
│   ├── in
│   │   ├── 1.in
│   │   ├── 2.in
│   │   └── 3.in
│   └── out
│       ├── 1.out
│       ├── 2.out
│       └── 3.out
└── userCode
    └── Main.c
```
<br>
다음과 같이 container를 실행시키면 userCode에 작성된 Main.c파일이 채점되는 것을 확인할 수 있습니다. 

```bash
docker run --rm \
-v ${PWD}/document/userCode:/home/code \
-e "MARKPATH=/home/code" \
-v ${PWD}/document/testCase:/home/tc \
-e "PROBPATH=/home/tc" \
codi_judge:3.0 sh -c './judge -l C99 -m 128 -s 1 -t 1' 
```
<br> 

코드와 테스트케이스가 작성된 디렉터리를 container내부와는 volume으로 공유합니다.     
judge 프로그램에는 환경변수(`MAKRPATH`, `PROBPATH`)로  컨테이너 내부의 코드와 테스트케이스있는 디렉터리를 주고, 다른 정보(채점언어, 메모리제한, 시간제한)는 인자로 넘겨줍니다.  

```bash
docker run --rm \
-v ${PWD}/document/userCode:/home/code \
-e "MARKPATH=/home/code" \ #=> 채점할 코드 디렉터리
-v ${PWD}/document/testCase:/home/tc \
-e "PROBPATH=/home/tc" \ #=> 테스트케이스 디렉터리 
codi_judge:3.0 sh -c \
'./judge -l C99 -m 128 -s 1 -t 1000' \ #=> 언어는 C99, heap/global memory는 128MB제한, stack은 1m 제한, 시간은 1000ms으로 제한
```
<br>

실행결과는 stdout으로 출력되는 것을 통해 확인할 수 있으며,
또한 채점할 코드가 위치한 디렉터리(document/userCode)에 result.json으로 작성됩니다. 

```json
//document/userCode/result.json
{
	"compile" : 1,
	"compile_msg" : "Main.c: In function 'main':\u000aMain.c:5:2: warning: ignoring return value of 'scanf', declared with attribute warn_unused_result [-Wunused-result]\u000a    5 |  scanf(\u0022%d%d\u0022, &a, &b);\u000a      |  ^~~~~~~~~~~~~~~~~~~~~\u000a" ,
	"result" : [
		{
		"memory" : 1848,
		"time" : 0,
		"CPUtime" : 0,
		"check" : 1,
		"msg" : "correct"
		}, 
		{
		"memory" : 1856,
		"time" : 0,
		"CPUtime" : 0,
		"check" : 1,
		"msg" : "correct"
		}, 
		{
		"memory" : 1860,
		"time" : 0,
		"CPUtime" : 0,
		"check" : 1,
		"msg" : "correct"
		}
	] 
}
```
<br>
<br>

# $ input format to judge program

사용자가 제출한 프로그램을 채점하기 위해서는 채점할 언어, 메모리/시간 제한, 테스트케이스 데이터, 사용자 코드 등의 정보가 필요합니다.     
이 중 일부는 judge 프로그램의 옵션으로 전달할 수 있으며, 일부는 파일로 작성한 다음 환경변수를 통하여 해당 파일의 위치를 알려줘야합니다.   
<br>
### judge program arguments(options)

채점할 언어와 시간, 메모리 제한은 judge 프로그램에 옵션으로 전달합니다. 

- -l : 채점할 language을 선택합니다. 다음과 같은 언어를 선택할 수 있습니다. `CPP11`, `CPP14`, `CPP17`, `PYTHON2`, `PYTHON3`, `C11`, `C99`, `JAVA11`

- -s : 사용자 코드를 실행할 때 제한할 stack 크기를 MB 단위로 입력합니다. 아무값도 주지 않으면 1MB가 기본적으로 적용됩니다.

- -m : 사용자 코드를 실행할때 제한할 heap, initialized/uninitialized data 메모리를 MB단위로 입력합니다. 아무값도 주지않으면 512MB가 적용됩니다.

- -t : 사용자 코드를 실행할 때 제한할 시간을  ms 단위로 입력합니다. 아무값도 주지 않을 경우는 2000ms가 기본적으로 적용됩니다.
<br>

### some files and environment variables

테스트 케이스(입,출력)과 채점할 코드는 모두 파일로 특정 디렉터리안에 작성해야합니다.     
이후 해당 디렉터리를 환경변수로 설정하면 judge 프로그램에서 해당 디렉터리에서 파일을 읽어오는 형태로 동작합니다. 
- 채점할 코드
    언어에 따라서 아래와 같이 소스코드명이 정해져 있습니다. <br>
    C : Main.c <br>
    C++ : Main.cpp <br>
    Python : Main.py <br>
    Java : Main.java <br>
    소스코드가 위치한 디렉터리를 `MARKPATH`라는 환경변수로 등록해야합니다.  
<br>

- 테스트케이스 데이터
    테스트 케이스 데이터는 입력의 경우 in이라는 폴더아래에, 출력의 경우 out이라는 폴더아래에 각 테스트케이스마다 별도의 파일로 작성되어야합니다. <br>
    테스트케이스 번호는 1번부터 순차적으로 증가해야하며, 입력은 [테스트케이스번호].in, 출력은 [테스트케이스번호].out으로 작성해야합니다. <br>
    테스트 케이스가 위치한 디렉터리 역시 `PROBPATH` 라는 환경 변수로 등록이 되어야합니다. 
<br>
<br>

# $ output file format of judge program
judge 프로그램이 실행되면 채점결과는 `MARKPATH`에 등록된 디렉터리 아래에 `result.json`파일로 작성됩니다.       
또한 테스트케이스별 제출한 코드의 실행결과파일도 [입력테스트케이스번호].out으로 저장됩니다.            
result.json 파일 포맷은 아래와 같습니다. 

| Name     |TYPE|Description|
|:----------:|:-------------:|------|
|compile|int  |1: compile success<br>0: compile fail |
|compile_msg |string |compile과정에서 발생한 메세지입니다. 컴파일 성공시에는 warning message,  컴파일 실패시에는 error message를 확인할 수 있습니다. |
|result |array |각 테스트 케이스별로 결과값이 array로 전달됩니다. |
|check|int|1 : execute success<br>0: execute fail|
|msg|string|execute fail시에 원인을 설명합니다. (ex."time limit exceeded", "runtime error", "memory limit exceeded", "wrong answer", "correct")|
|memory|int|메모리사용량(KB)|
|time|int|실행시간(ms)|
|CPUtime|int|cpu clock 기준으로 계산된 실행시간, 멀티스레드를 사용한다면 time보다 더 큰 시간이 측정됩니다|
    

