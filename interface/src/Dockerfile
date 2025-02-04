FROM node:21-alpine

COPY public/ /app/public
COPY src/ /app/src
COPY package.json /app/

WORKDIR "/app"

RUN npm install

CMD ["npm", "start"]