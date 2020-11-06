# Codieater
**코드를 먹어서 뱉어주겠다.**

**온라인 저지(코드 채점) 프로그램.**

## Requirement
- Node.js >= 14.x
- Yarn
- docker

## Run
```
$ cd docker/pg
$ docker build -f pg.dockerfile .
$ cd ../judge
$ docker build -f judge.dockerfile .
```
도커로 돌릴 postgres와 judge 도커파일을 빌드해서 이미지로 만든다.


```
$ cd ../../server
$ ./run.sh
```
node를 돌릴 모듈들과 db migrate 및 seeding.

이후 자동으로 5000번 포트로 웹 서버 구동.


```
http://localhost:5000
```
로컬 테스트 개발 주소

## Caution
- server/src/constrollers/judgeController.js의 4번째 줄 PWD 변수를 자신에 맞는 PWD로 수정해야함.
- run.sh를 실행하면 관리자 모드가 필요한 경우가 있으므로 오류가 날시 sudo를 붙여야 합니다.
- run.sh를 실행하고 DB쪽에 오류가 나서 다시 실행할 때 'asd' 컨테이너 존재로 오류가 날 시 
```
docker stop asd
docker rm asd
```
명령어를 쓰고 다시 실행 시켜야 합니다.

추후 예외처리 할 예정.

## Contributors
- 윤승희 / <zetwhite@naver.com> / 코드 채점 judge 내부 개발 담당
- 전설 / <rafch@naver.com> / 도커, 개발환경 개발 담당


## Reference
- node -  MIT License 
- postgres - PostgreSQL License - <https://www.postgresql.org/about/licence/>
- docker - Apache License 2.0


## License
- [MIT](http://opensource.org/licenses/MIT)
