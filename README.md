# ReasonReact Todo with Hasura Data APIs

This quickstart will give you a Reason React project for a simple Todo application, integrated with Hasura's data APIs to insert and delete data from the database.

![Todo](https://raw.githubusercontent.com/anirudhmurali/ReasonReact-Todo/master/ReasonReact.png)

This quickstart makes use of [https://redex.github.io/packages/unpublished/glennsl/refetch](glennsl/refetch) to send HTTP requests, which are handled using Hasura's data APIs.

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