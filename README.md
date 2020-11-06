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
도커로 돌릴 postgres와 judge 이미지를 빌드해서 이미지로 만든다.


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


## Contributors
- 윤승희 / <zetwhite@naver.com> / 코드 채점 judge 내부 개발 담당
- 전설 / <rafch@naver.com> / 도커, 개발환경 개발 담당


## Reference
- node -  MIT License 
- postgres - PostgreSQL License - <https://www.postgresql.org/about/licence/>
- docker - Apache License 2.0


## License
- [MIT](http://opensource.org/licenses/MIT)
