type item = {
  id: int,
  title: string,
  completed: bool
};

let str = ReasonReact.stringToElement;
let insert = (text) => {
Resync.(Refetch.(
  request(`POST, "https://data.abstemiously42.hasura-app.io/v1/query")
    |> Request.header(`ContentType("application/json"))
    |> Request.payload(`String("{\"type\":\"insert\",\"args\":{\"table\":\"todo\",\"objects\":[{\"Task Name\":\""++text++"\"}]}}"))
  |> fetch
  |> Future.flatMap(
        fun | Response.Ok(_, response) => Response.text(response)
            | Response.Error({ reason }, _) => Future.from(reason))
    |> Future.whenResolved(Js.log)
));
};

let delete = (text) => {
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
};

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, ~onToggle, children) => {
    ...component,
    render: (_) =>
      <div className="item" onClick=((evt) => onToggle())>
      <input
        _type="checkbox" onClick=( (evt) => delete(item.title))
        checked=(Js.Boolean.to_js_boolean(item.completed))
      />
        (str(item.title))

      </div>
  };
};

let valueFromEvent = (evt) : string => (
  evt
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
)##value;


module Input = {
  type state = string;
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    reducer: (newText, _text) => ReasonReact.Update(newText) ,
    render: ({state: text, reduce}) =>
      <input
        value=text
        _type="text"
        placeholder="Write something to do"
        onChange=(reduce((evt) => valueFromEvent(evt)))
        onKeyDown=((evt) =>
          if (ReactEventRe.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            insert(text);
            (reduce(() => ""))()
          }

        )
      />
  };
};

type state = {
  items: list(item)
};
type action =
  | AddItem(string)
  | ToggleItem(int);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);
let newItem = (text) => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, completed: false}
};
let make = (children) => {
  ...component,
  initialState: () => {
    items: [{
      id: 0,
      title: "Add your entries here..",
      completed: false
    }]
  },
  reducer: (action, {items}) =>
    switch action {
    | AddItem(text) => ReasonReact.Update({items: [newItem(text), ...items]})
    | ToggleItem(id) =>
      let items =
        List.map(
          (item) =>
            item.id === id ?
              {...item, completed: ! item.completed} : item,
          items
        );
      ReasonReact.Update({items: items})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (str("What to do"))
        <Input onSubmit=(reduce((text) => AddItem(text))) />
      </div>
      <div className="items">
        (
          ReasonReact.arrayToElement(Array.of_list(List.map(
            (item) =>
              <TodoItem
                key=(string_of_int(item.id))
                onToggle=(reduce(() => ToggleItem(item.id)))
                item
              />,
            items
          )))
        )
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ " items"))
      </div>
    </div>
  }
};
