FROM node

WORKDIR /src

RUN npm install

ADD src /src

RUN yarn start

RUN yarn build

RUN yarn global add serve

CMD ["serve", "-s", "public", "-p", "8080"]
