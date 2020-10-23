FROM node:14.14.0-alpine3.12

WORKDIR /home/Codieater

ENTRYPOINT [ "/home/Codieater/run.sh" ]

CMD [ "yarn", "dev" ]