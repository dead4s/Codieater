# Codieater
<img width="200" src="https://user-images.githubusercontent.com/61981457/99392262-c83b0180-291e-11eb-9dae-cc07ab454bdf.jpg">

**코드를 먹어서 뱉어주겠다.**

**온라인 저지(코드 채점) 프로그램.**

## Requirement
- Node.js == 14.x
- Yarn
- docker

## Run
```
$ git clone https://github.com/Codieater/Codieater.git
$ cd Codieater
$ docker build -t codi_db:1.0 -f docker/pg.dockerfile .
$ docker build -t codi_judge:3.0 -f docker/judge.dockerfile .
```
도커로 돌릴 postgres와 judge 도커파일을 빌드해서 이미지로 만든다.


```
$ cd server
$ ./run.sh
```
node를 돌릴 모듈 다운과 db migrate 및 seeding.

이후 자동으로 5000번 포트로 웹 서버 구동.


```
http://localhost:5000
```
로컬 테스트 개발 주소


## More documents
- [judge program(container) input and output](https://github.com/Codieater/Codieater/blob/main/document/Judge_Input_Output.md)


## Caution
- run.sh를 실행하면 관리자 모드가 필요한 경우가 있으므로 오류가 날시 sudo를 붙여야 합니다.

## Contributors
- 윤승희 / <zetwhite@naver.com> / 코드 채점 judge 내부 개발 담당
- 전설 / <rafch@naver.com> / 도커, 개발환경 개발 담당

## License
- [MIT](http://opensource.org/licenses/MIT)
