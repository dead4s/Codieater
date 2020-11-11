From ubuntu:20.04
MAINTAINER YounSeungHui <zetwhite@naver.com>

RUN apt-get update && apt-get install -y --no-install-recommends apt-utils 
RUN apt-get install -y gcc g++ python3 python2 build-essential openjdk-8-jdk-headless
RUN apt-get install -y libseccomp-dev

#COPY ../../judge /home/judge

WORKDIR /home/judge
