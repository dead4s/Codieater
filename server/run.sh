#!/bin/sh

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
	yarn db:seed
fi

yarn dev