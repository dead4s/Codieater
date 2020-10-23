#!/bin/sh

yarn
yarn db:create

if [ $? -eq 0 ];then
	yarn db:migrate
	yarn db:seed
fi

exec "$@"