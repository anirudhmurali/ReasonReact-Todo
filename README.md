# ReasonReact Todo with Hasura Data APIs

## What does this come with?

* [ReasonReact](https://reasonml.github.io/reason-react/) Todo app written with [ReasonML](http://reasonml.github.io)
* Making API requests with [refetch](https://redex.github.io/packages/unpublished/glennsl/refetch)
* Served with [`serve`](https://www.npmjs.com/package/serve) package
* Hot-reloading, instantly view the changes upon every save
* Cloud-ready Dockerfile deployment

```
FROM node

WORKDIR /src

ADD src /src

RUN npm install

RUN yarn start

RUN yarn build

RUN yarn global add serve

CMD ["serve", "-s", "public", "-p", "8080"]
``` 

## Deploy this ReasonReact Todo app instantly!

Press the **Clone & Deploy** button and follow the instructions to clone the quickstart. Browse to `/microservices/www/src` and edit the ReasonML files in `src` folder according to your app. The current serving files are being stored at `public` folder, make sure you update the Dockerfile if you change the structure of the project.

## Architecture of behind the scenes

## Adding Database functionality

You can track the insertion/deletion responses in your browser's console window. Open the API console with the command `hasura api-console` in your terminal, and view the **Data** section to see the data being inserted and deleted. 

You can find the below piece of code in `microservices/www/src/src/TodoApp.re`. Update your cluster name in the two blocks of code. The first one is for inserting the Todo contents, and the second function block is to delete the entry upon toggling.


```
Resync.(Refetch.(
  request(`POST, "https://data.<cluster_name>.hasura-app.io/v1/query")
    |> Request.header(`ContentType("application/json"))
    |> Request.payload(`String("<stringified_JSON>"}}}}"))
  |> fetch
  |> Future.flatMap(
        fun | Response.Ok(_, response) => Response.text(response)
            | Response.Error({ reason }, _) => Future.from(reason))
    |> Future.whenResolved(Js.log)
));
```

Below is an example request:

```
Resync.(Refetch.(
  request(`POST, "https://data.abstemiously42.hasura-app.io/v1/query")
    |> Request.header(`ContentType("application/json"))
    |> Request.payload(`String("{\"type\":\"delete\",\"args\":{\"table\":\"todo\",\"where\":{\"Task Name\":{\"$eq\":\""++text++"\"}}}}"))
  |> fetch
  |> Future.flatMap(
        fun | Response.Ok(_, response) => Response.text(response)
            | Response.Error({ reason }, _) => Future.from(reason))
    |> Future.whenResolved(Js.log)
));
```

## Adding Authentication to the App


## Next steps:

* [Adding Authentication](https://docs.hasura.io/0.15/manual/gateway/index.html)
* [Change subdomain](https://docs.hasura.io/0.15/manual/gateway/index.html#custom-domains)
* [Adding Microservice](https://docs.hasura.io/0.15/manual/custom-microservices/index.html)

### Resources:

* [Reason Package Index](https://redex.github.io/)
* [ReasonReact](https://reasonml.github.io/reason-react/)
* [ReasonReact Example](https://github.com/jaredly/a-reason-react-tutorial)