const ccengine = require("ccengine");

var engine = ccengine.create();
var setting = null;
var listener = null;
var aiCallbak = null;
var actionCallback = null;

exports.onStateChanged = function(callback) {
  listener = callback;
};

exports.onAIStateChanged = function(callback) {
  aiCallbak = callback;
};

exports.onAction = function(callback) {
  actionCallback = callback;
}

exports.getState = function() {
  return engine.getState();
};

exports.getPlayer = function() {
  return engine.getPlayer() == 0 ? "red" : "black";
};

exports.getLastMove = function() {
  return engine.getLastMove();
};

exports.goBack = function() {
  if (!setting)
    return;
  engine.undo();
  if (typeof listener == "function")
    listener();
};

function aiGo() {
  if (engine.getPlayer() == 0 && setting.redSide == "ai") { // red side
    setTimeout(function(){
      typeof aiCallbak == "function" && aiCallbak("start");
      engine.findSolution(setting.level, function(movement) {
        typeof aiCallbak == "function" && aiCallbak("stop");
        if (movement) {
          exports.go(movement);
        }
      });
    }, 700);
  } else if (engine.getPlayer() == 1 && setting.blackSide == "ai") {
    setTimeout(function(){
      typeof aiCallbak == "function" && aiCallbak("start");
      engine.findSolution(setting.level, function(movement) {
        typeof aiCallbak == "function" && aiCallbak("stop");
        if (movement) {
          exports.go(movement);
        }
      });
    }, 700);
  }
}

exports.go = function(movement) {
  if (!setting)
    return;
  var result;
  if (arguments.length == 1) {
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

exports.newGame = function(option) {
  if (!option) {
    option = {};
    option.color = "red";
    option.level = 3;
    option.redSide = "human";
    option.blackSide = "ai";
  }
  let color = 0;
  if (option && option.color == 'black') {
    color = 1;
  }
  engine.startup(color);
  setting = option;
  if (typeof listener == "function")
    listener();
  if (option.redSide == "ai") {
    setTimeout(function() {
      aiGo();
    }, 1000);
  }
};

exports.setPlayer = function(option) {
  if (!setting)
    return;
  setting.redSide = option.redSide;
  setting.blackSide = option.blackSide;
};