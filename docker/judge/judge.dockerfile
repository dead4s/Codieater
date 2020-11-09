From ubuntu:20.04
MAINTAINER YounSeungHui <zetwhite@naver.com>

RUN apt-get update
RUN apt-get install -y --no-install-recommends gcc g++ python3 python2 build-essential openjdk-8-jdk-headless openjdk-11-jdk-headless

#COPY ../../judge /home/judge

WORKDIR /home/judge

#RUN cd /home/judge && make

CMD ["sh", "-c", "tail -f /dev/null"]
