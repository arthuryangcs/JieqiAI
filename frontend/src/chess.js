// const ccengine = require("ccengine");

const engine = {};
let setting = null;
let listener = null;
let aiCallback = null;
let actionCallback = null;

// 开局
let board = [
    20, 19, 18, 17, 16, 17, 18, 19, 20,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 21, 0, 0, 0, 0, 0, 21, 0,
    22, 0, 22, 0, 22, 0, 22, 0, 22,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    14, 0, 14, 0, 14, 0, 14, 0, 14,
    0, 13, 0, 0, 0, 0, 0, 13, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    12, 11, 10, 9, 8, 9, 10, 11, 12,
]

engine.board = []
engine.player = 0

engine.startup = function (color) {
    engine.board = [...board];
}

engine.findSolution = function (level, move) {
    // todo: 修改 ai 走棋
    move();
}

engine.move = function (movement) {
    // todo: remove
    console.log("move", movement);

    if (arguments.length !== 4) {
        return "go";
    }

    let sourceX = arguments[0], sourceY = arguments[1], targetX = arguments[2], targetY = arguments[3];
    engine.board[targetY * 9 + targetX] = engine.board[sourceY * 9 + sourceX];
    engine.board[sourceY * 9 + sourceX] = 0;

    engine.player = 1 - engine.player

    return "go";
}

engine.getPlayer = function () {
    return engine.player;
}

engine.getLastMove = function () {
    return 0;
}

engine.getState = function () {
    return {
        over: false,
        winner: null,
        board: engine.board,
    }
}

exports.onStateChanged = function (callback) {
    listener = callback;
};

exports.onAIStateChanged = function (callback) {
    aiCallback = callback;
};

exports.onAction = function (callback) {
    actionCallback = callback;
}

exports.getState = function () {
    return engine.getState();
};

exports.getPlayer = function () {
    return engine.getPlayer() === 0 ? "red" : "black";
};

exports.getLastMove = function () {
    return engine.getLastMove();
};

exports.goBack = function () {
    if (!setting)
        return;
    engine.undo();
    if (typeof listener == "function")
        listener();
};

function aiGo() {
    if (engine.getPlayer() === 0 && setting.redSide === "ai") { // red side
        setTimeout(function () {
            typeof aiCallback == "function" && aiCallback("start");
            engine.findSolution(setting.level, function (movement) {
                typeof aiCallback == "function" && aiCallback("stop");
                if (movement) {
                    exports.go(movement);
                }
            });
        }, 700);
    } else if (engine.getPlayer() === 1 && setting.blackSide === "ai") {
        setTimeout(function () {
            typeof aiCallback == "function" && aiCallback("start");
            engine.findSolution(setting.level, function (movement) {
                typeof aiCallback == "function" && aiCallback("stop");
                if (movement) {
                    exports.go(movement);
                }
            });
        }, 700);
    }
}

exports.go = function (movement) {
    console.log("move", arguments.length, ...arguments, movement);
    if (!setting)
        return;
    let result;
    if (arguments.length === 1) {
        result = engine.move(movement);
    } else {
        result = engine.move(...arguments);
    }
    if (!result) {
        typeof actionCallback == "function" && actionCallback("wrong");
        return false;
    } else {
        if (typeof listener == "function")
            listener();
        typeof actionCallback == "function" && actionCallback("go");
    }

    aiGo();

    return true;
};

exports.newGame = function (option) {
    if (!option) {
        option = {};
        option.color = "red";
        option.level = 3;
        option.redSide = "human";
        option.blackSide = "ai";
    }
    let color = 0;
    if (option && option.color === 'black') {
        color = 1;
    }
    engine.startup(color);
    setting = option;
    if (typeof listener == "function")
        listener();
    if (option.redSide === "ai") {
        setTimeout(function () {
            aiGo();
        }, 1000);
    }
};

exports.setPlayer = function (option) {
    if (!setting)
        return;
    setting.redSide = option.redSide;
    setting.blackSide = option.blackSide;
};