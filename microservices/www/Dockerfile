FROM node:6

RUN npm install -g bs-platform 

WORKDIR /src

ADD src /src

RUN npm install

RUN npm link bs-platform

RUN yarn start

RUN yarn build

RUN yarn global add serve

CMD ["serve", "-s", "public", "-p", "8080"]
