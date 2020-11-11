From ubuntu:20.04
MAINTAINER YounSeungHui <zetwhite@naver.com>

RUN apt-get update
RUN apt-get install -y gcc g++ python3 python2 build-essential 

WORKDIR /home/judge

# CMD ["sh", "-c", "tail -f /dev/null"]