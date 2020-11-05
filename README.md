# Codieater
**코드를 먹어서 뱉어주겠다.**

**온라인 저지(코드 채점) 프로그램.**

## Requirement
- Node.js >= 14.x
- Yarn
- docker
- docker-compose

## Run
```
$ cd docker
$ docker-compose build
$ docker-compose up -d
```
서버인 node는 node container에서 필요한 모듈을 다운 받고 종료

DB인 postgres는 db container 실행 후 백그라운드 동작


```
$ cd ../server
$ yarn dev
```
서버는 docker container에서가 아닌 호스트에서 실행


```
http://localhost:5000
```
로컬 테스트 개발 주소


## Contributors
- 윤승희 / <zetwhite@naver.com> / 코드 채점 judge 내부 개발 담당
- 전설 / <rafch@naver.com> / 도커, 개발환경 개발 담당


## Reference
- DMOJ - <https://github.com/DMOJ/judge-server>
- compilebox - <https://github.com/remoteinterview/compilebox>
- QingdaoU - <https://github.com/QingdaoU/Judger>


## License
- node -  MIT License
- postgres - PostgreSQL License - <https://www.postgresql.org/about/licence/>
- docker - Apache License 2.0
- C++ STL