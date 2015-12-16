var addon = require('bindings')('addon');

addon({
    "obj": {
        "a": "a",
        "b": "b"
    },
    "arr": [1, 2, 3],
    "undefined": undefined,
    "null": null,
    "func": function(msg) {
        console.log(msg);
    },
    "bool_true": true,
    "bool_false": false,
    "date": new Date()
});
