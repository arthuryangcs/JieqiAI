const engine = require("./chess.js");
const ipcRenderer = require("electron").ipcRenderer;
const fs = require('fs');
const os = require('os');

window.$ = document.getElementById.bind(document);
const canvas = $("chessBoard");

function onResize() {
  canvas.style.height = "";
  canvas.style.width = Math.floor(window.innerWidth) + "px";
  canvas.style.height = Math.floor(canvas.clientHeight) + "px";
  canvas.setAttribute("width", canvas.clientWidth);
  canvas.setAttribute("height", canvas.clientHeight);
  draw();
}

window.onresize = onResize;
window.onload = function() {
  loadConfig();
  engine.newGame(setting);
  onResize();
}

let config = null;

function loadConfig() {
  const configFile = os.homedir() + '/.jieqiai/config.json';
  try {
    var buffer = fs.readFileSync(configFile, 'utf8');
    config = JSON.parse(buffer);
  } catch(e) {
    config = {
      theme: "dark"
    };
  }
}


var setting = {
  color: "red",
  redSide: "human",
  blackSide: "ai",
  level: 3
};
let activePos = null;
let gameState = null;
let player = null;
let aiState = null;
let lastMove = null;

function newGame(color) {
  setting.color = color;
  setting.redSide = (color === "red" ? "human" : "ai");
  setting.blackSide = (color === "black" ? "human" : "ai");
  engine.newGame(setting);
}

engine.onStateChanged(function() {
  activePos = null;
  gameState = engine.getState();
  player = engine.getPlayer();
  lastMove = engine.getLastMove();
  $("statusBar").innerHTML = (player === "red" ? "该红方走棋" : "该黑方走棋");
  draw();
  if (gameState.over) {
    if (gameState.winner) {
      if (gameState.winner === "red") {
        $("statusBar").innerHTML = "红方胜！";
        setTimeout(function() {msgbox("红方胜！");}, 100);
      } else {
        $("statusBar").innerHTML = "黑方胜！";
        setTimeout(function() {msgbox("黑方胜！");}, 100);
      }
    } else {
      $("statusBar").innerHTML = "和棋！";
      setTimeout(function() {msgbox("和棋！");}, 100);
    }
  }
});

engine.onAIStateChanged(function(state) {
  aiState = state;
  if (state === "start") {
    $("statusBar").innerHTML = "计算机正在思考...";
  }
});

engine.onAction(function(action) {
  const audio = $("sound");
  audio.type = "audio/wav";
  if (action === "go") {
    if (gameState.over && gameState.winner === setting.color) {
      audio.src = "sound/win.wav";
    } else if (gameState.over && gameState.winner && gameState.winner !== setting.color) {
      audio.src = "sound/loss.wav";
    } else if (gameState.over) {
      audio.src = "sound/draw.wav";
    } else if (gameState.checked) {
      audio.src = "sound/check.wav";
    } else if (gameState.captured) {
      audio.src = "sound/captured.wav";
    } else
      audio.src = "sound/move.wav";
    audio.play();
  } else if (action === "wrong") {
    audio.src = "sound/wrong.wav";
    audio.play();
  }
});

function askbox(msg, callback) {
  ipcRenderer.once("askCallBack", function(e, result) {
    typeof callback == "function" && callback(result);
  });
  ipcRenderer.send("confirmDialog", msg, "askCallBack");
}

function msgbox(msg) {
  ipcRenderer.send("infoDialog", msg);
}

ipcRenderer.on("chess", function(e, args) {
  if (args === "goBack" && aiState !== "start") {
    if (player === setting.color) {
      if (player === setting.color && setting.blackSide === "ai") {
        // engine.goBack();
        // engine.goBack();
      } else if (player === setting.color && setting.redSide === "ai") {
        // engine.goBack();
        // engine.goBack();
      } else {
        // engine.goBack();
      }
    } else {
      if (player === setting.color && setting.blackSide !== "ai") {
        // engine.goBack();
      } else if (player === setting.color && setting.redSide !== "ai") {
        // engine.goBack();
      }
    }
  } else if (args === "changeTheme") {
    config.theme = arguments[2];
    draw();
  } else if (args === "newGameRed" || args === "newGameBlack") {
    if (aiState === "start") {
      return;
    }
    if (!gameState.over) {
      askbox("要放弃当前棋局吗？", function(result){
        if (result !== 1) {
          return;
        }
        newGame(args === "newGameRed" ? "red" : "black");
      });
    } else {
      newGame(args === "newGameRed" ? "red" : "black");
    }
  } else if (args === "about") {
    msgbox("Jieqi AI\n\nAuthor: Arthur Yang\nE-Mail: ArthurYangCS@gmail.com\nLicense: GPL-3.0");
  }
});

function getBoardRect() {
  let cw = canvas.width;
  let ch = canvas.height;
  let ratio = cw / ch;
  const NR = 10 / 11;
  let w, h, c;
  if (ratio > NR) { // caculate by height
    c = Math.floor(ch / 11);
    if (c % 2 === 1)
      c--;
    h = c * 9;
    w = c * 8;
  } else { // caculate by width
    c = Math.floor(cw / 10);
    if (c % 2 === 1)
      c--;
    h = c * 9;
    w = c * 8;
  }
  let left = (cw - w) / 2;
  if (left % 2 === 1)
    left--;
  let top = (ch - h) / 2;
  if (top % 2 === 1)
    top--;
  return {
    cell: c,
    left: Math.floor(left),
    top: Math.floor(top),
    width: w,
    height: h
  };
}

const chessName = [
  0, 0, 0, 0, 0, 0, 0, 0,
  "r:帅","r:仕","r:相","r:马","r:车","r:炮","r:兵", 0,
  "b:将","b:士","b:象","b:马","b:车","b:炮","b:卒", 0
];

const soldierLines = [[1, 2], [7, 2], [1, 7], [7, 7], [0, 3], [2, 3], [4, 3], [6, 3], [8, 3], [0, 6], [2, 6], [4, 6], [6, 6], [8, 6]];
const crossLines = [[3, 0, 5, 2], [5, 0, 3, 2], [3, 9, 5, 7], [5, 9, 3, 7]];

function getName(index) {
  let txt = chessName[index];
  if (txt) {
    return txt.substring(2);
  } else {
    return null;
  }
}
function getColor(index) {
  let txt = chessName[index];
  if (txt) {
    return txt.substring(0, 1);
  } else {
    return null;
  }
}
const { themes } = require("./theme.js");
function getThemeColor(type) {
  return themes[config.theme][type];
}

function draw() {
  const rc = getBoardRect();
  const ctx = canvas.getContext("2d");
  ctx.save();

  // ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.fillStyle = getThemeColor("background");
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  function drawChessman(x, y, name, color) {
    ctx.beginPath();
    if (color === "r") {
      ctx.fillStyle = getThemeColor("redChessman");
    } else {
      ctx.fillStyle = getThemeColor("blackChessman");
    }
    ctx.lineWidth = 3;
    ctx.arc(rc.left + rc.cell * x, rc.top + rc.cell * y, rc.cell / 2 - 4, 0, 360);
    //ctx.stroke();
    ctx.shadowColor = getThemeColor("shadow");
    ctx.shadowBlur = 1;
    ctx.shadowOffsetY = 1;
    ctx.shadowOffsetX = 1;
    ctx.fill();

    let s = Math.floor(rc.cell / 8);

    ctx.beginPath();
    ctx.font = Math.floor(rc.cell / 2) - 2 + 'px monospace';
    ctx.textAlign = 'center';
    ctx.textBaseline = "middle";
    if (color === "r") {
      ctx.fillStyle = getThemeColor("redText");
    } else {
      ctx.fillStyle = getThemeColor("blackText");
    }
    ctx.shadowBlur = 0;
    ctx.shadowColor = 'transparent';
    ctx.shadowOffsetY = 0;
    ctx.shadowOffsetX = 0;
    ctx.fillText(name, rc.left + rc.cell * x, rc.top + rc.cell * y + 2);
    ctx.beginPath();
    ctx.lineWidth = 1;
    if (color === "r") {
      ctx.strokeStyle = getThemeColor("redBorder");
    } else {
      ctx.strokeStyle = getThemeColor("blackBorder");
    }

    ctx.arc(rc.left + rc.cell * x, rc.top + rc.cell * y, rc.cell / 2 - s, 0, 360);
    ctx.stroke();
  }

  ctx.beginPath();
  ctx.lineWidth = 1;
  ctx.strokeStyle = getThemeColor("line");
  ctx.translate(-0.5, -0.5);
  ctx.strokeRect(rc.left, rc.top, rc.width, rc.height);

  for (let y = 1; y <= 8; y++) {
    ctx.moveTo(rc.left, rc.top + rc.cell * y);
    ctx.lineTo(rc.left + rc.width, rc.top + rc.cell * y);
  }

  for (let x = 1; x <= 7; x++) {
    ctx.moveTo(rc.left + rc.cell * x, rc.top);
    ctx.lineTo(rc.left + rc.cell * x, rc.top + rc.cell * 4);

    ctx.moveTo(rc.left + rc.cell * x, rc.top + rc.cell * 5);
    ctx.lineTo(rc.left + rc.cell * x, rc.top + rc.height);
  }


  for (let pt of soldierLines) {
    let x = pt[0], y = pt[1];
    let c = rc.cell;
    let s = Math.floor(rc.cell / 10);
    let l = rc.left;
    let t = rc.top;
    let scale = 3;
    if (x !== 0) {
      ctx.moveTo(l + c * x - s, t + c * y - s * scale);
      ctx.lineTo(l + c * x - s, t + c * y - s);
      ctx.moveTo(l + c * x - s, t + c * y + s * scale);
      ctx.lineTo(l + c * x - s, t + c * y + s);
      ctx.moveTo(l + c * x - s * scale, t + c * y - s);
      ctx.lineTo(l + c * x - s, t + c * y - s);
      ctx.moveTo(l + c * x - s * scale, t + c * y + s);
      ctx.lineTo(l + c * x - s, t + c * y + s);
    }
    if (x !== 8) {
      ctx.moveTo(l + c * x + s, t + c * y - s * scale);
      ctx.lineTo(l + c * x + s, t + c * y - s);
      ctx.moveTo(l + c * x + s, t + c * y + s * scale);
      ctx.lineTo(l + c * x + s, t + c * y + s);
      ctx.moveTo(l + c * x + s * scale, t + c * y - s);
      ctx.lineTo(l + c * x + s, t + c * y - s);
      ctx.moveTo(l + c * x + s * scale, t + c * y + s);
      ctx.lineTo(l + c * x + s, t + c * y + s);
    }
  }
  ctx.stroke();
  ctx.beginPath();

  for (let line of crossLines) {
    let c = rc.cell;
    let l = rc.left;
    let t = rc.top;
    ctx.moveTo(l + line[0] * c, t + line[1] * c);
    ctx.lineTo(l + line[2] * c, t + line[3] * c);
  }
  ctx.strokeStyle = getThemeColor("crossLine");
  ctx.stroke();
  ctx.lineWidth = 1;
  ctx.strokeStyle = getThemeColor("border");
  ctx.strokeRect(rc.left - 2, rc.top - 2, rc.width + 4, rc.height + 4);

  let radius = Math.floor(rc.cell / 2);

  if (activePos) {
    ctx.save();
    ctx.strokeStyle = getThemeColor("selection");
    ctx.lineWidth = 2;
    ctx.strokeRect(rc.left + rc.cell * activePos.x - radius, rc.top + rc.cell * activePos.y - radius, rc.cell, rc.cell);
    ctx.restore();
  }

  if (lastMove) {
    ctx.save();
    ctx.setLineDash([2]);
    ctx.strokeStyle = getThemeColor("lastMove");
    ctx.lineWidth = 2;
    ctx.beginPath();
    // ctx.arc(rc.left + lastMove[0] * rc.cell, rc.top + lastMove[1] * rc.cell, radius - 2, 0, 360);
    // ctx.stroke();
    // ctx.beginPath();
    // ctx.arc(rc.left + lastMove[2] * rc.cell, rc.top + lastMove[3] * rc.cell, radius - 2, 0, 360);
    ctx.rect(rc.left + lastMove[0] * rc.cell - radius + 2, rc.top + lastMove[1] * rc.cell - radius + 2, rc.cell - 4, rc.cell - 4);
    ctx.rect(rc.left + lastMove[2] * rc.cell - radius + 2, rc.top + lastMove[3] * rc.cell - radius + 2, rc.cell - 4, rc.cell - 4);

    ctx.stroke();
    ctx.restore();
  }

  if (gameState) {
    for (let y = 0; y < 10; y++) {
      for (let x = 0; x < 9; x++) {
        let v = gameState.board[y * 9 + x];
        if (v !== 0) {
          drawChessman(x, y, getName(v), getColor(v));
        }
      }
    }
  }

  ctx.translate(0.5, 0.5);
  ctx.restore();
}


function distance(pt1, pt2) {
  return Math.sqrt(Math.pow(pt2.x - pt1.x, 2)
      + Math.pow(pt2.y - pt1.y, 2));
}

canvas.onclick = function(e) {
  if (!gameState || gameState.over)
    return;
  const rc = getBoardRect();
  const radius = Math.floor(rc.cell / 2) - 4;
  const x = Math.floor((e.x - rc.left + rc.cell / 2) / rc.cell);
  var y = Math.floor((e.y - rc.top + rc.cell / 2) / rc.cell);
  if (x > 8 || y > 9)
    return;
  var px = rc.left + x * rc.cell;
  var py = rc.top + y * rc.cell;
  var dist = distance({x: px, y: py}, {x: e.x, y: e.y} );
  if (dist <= radius) {
    var v = gameState.board[y * 9 + x];
    if (getColor(v) === 'r' && player === "red" && setting.color === player) {
      activePos = {x: x, y: y};
      draw();
    } else if (getColor(v) === 'b' && player === "black" && setting.color === player) {
      activePos = {x: x, y: y};
      draw();
    } else if (activePos) {
      engine.go(activePos.x, activePos.y, x, y);
    }
  }
};