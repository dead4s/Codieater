#!/bin/sh

echo "NODE_ENV=development\n\
DATABASE=ccm\n\
HOST=127.0.0.1\n\
USERNAME=codi\n\
PASSWORD=codicodi\n\
PORT=5000\n\
PWD=$(pwd)" > .env

docker stop asd
sleep 1
docker rm asd

docker run \
	-d \
	--name asd \
	-e POSTGRES_USER=codi \
	-e POSTGRES_PASSWORD=codicodi \
	-e LANG=ko_KR.utf8 \
	-p 5432:5432 \
	codi_db:1.0

yarn
sleep 1
yarn db:create

if [ $? -eq 0 ];then
	yarn db:migrate
	yarn db:seed --seed 20201105164101-user.js
fi

yarn dev