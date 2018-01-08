# ReasonReact Todo with Hasura Data APIs

This quickstart will give you a Reason React project for a simple Todo application, integrated with Hasura's data APIs to insert and delete data from the database.

![Todo](https://raw.githubusercontent.com/anirudhmurali/ReasonReact-Todo/master/ReasonReact.png)

**ReasonML** lets you write simple, fast and quality type safe code while leveraging both the JavaScript & OCaml ecosystems.

This quickstart uses [**ReasonReact**](https://reasonml.github.io/reason-react/). ReasonReact is a way to build React components with Reason. This project makes use of [glennsl/refetch](https://redex.github.io/packages/unpublished/glennsl/refetch) package to send HTTP requests, which are handled using Hasura's data APIs.

You can find the below piece of code in `microservices/www/src/src/TodoApp.re`.

Update your cluster name in the two blocks of code. The first one is for inserting the Todo contents, and the second function block is to delete the entry upon toggling.

You can track the insertion/deletion responses in your browser's console window. Open the API console with the command `hasura api-console` in your terminal, and view the **Data** section to see the data being inserted and deleted.

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

### Resources:

* [Reason Package Index](https://redex.github.io/)
* [ReasonReact](https://reasonml.github.io/reason-react/)
* [ReasonReact Example](https://github.com/jaredly/a-reason-react-tutorial)