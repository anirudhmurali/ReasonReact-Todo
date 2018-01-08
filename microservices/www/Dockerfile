FROM node

WORKDIR /src

ADD src /src

RUN npm install

RUN yarn start

RUN yarn build

RUN yarn global add serve

CMD ["serve", "-s", "public", "-p", "8080"]
