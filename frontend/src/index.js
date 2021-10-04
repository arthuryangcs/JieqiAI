const electron = require('electron');
// Module to control application life.
const app = electron.app
// Module to create native browser window.
const BrowserWindow = electron.BrowserWindow

const path = require('path')
const url = require('url')
const fs = require('fs');
const os = require('os');
const {themes} = require("./theme.js");

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let mainWindow

let config = null;

function loadConfig() {
    const configFile = os.homedir() + '/.jieqiai/config.json';
    try {
        const buffer = fs.readFileSync(configFile, 'utf8');
        config = JSON.parse(buffer);
    } catch (e) {
        config = {
            size: 2,
            theme: "dark"
        };
    }
}

function saveConfig() {
    try {
        const path = os.homedir() + '/.jieqiai';
        if (!fs.existsSync(path)) {
            fs.mkdirSync(path);
        }
        const configFile = path + '/config.json';
        // fs.unlinkSync(configFile);
        fs.writeFileSync(configFile, JSON.stringify(config), {
            encoding: 'utf8',
            flag: "w"
        });
    } catch (e) {
        console.log("Save config failed.", e);
    }
}

function getWindowSizeConfig() {
    if (config.size === 1) {
        return [400, 500];
    } else if (config.size === 2) {
        return [600, 700];
    } else {
        return [850, 960];
    }
}

function changeWindowSize() {
    const size = getWindowSizeConfig();
    mainWindow.setSize(size[0], size[1]);
}

function changeTheme() {
    mainWindow.webContents.send("chess", "changeTheme", config.theme);
}

function createMenu() {
    const menu = electron.Menu.buildFromTemplate([
        {
            label: "Game",
            submenu: [
                {
                    label: "New Game (As Red Side)",
                    accelerator: "R",
                    click: function () {
                        mainWindow.webContents.send("chess", "newGameRed");
                    }
                }, {
                    label: "New Game (As Black Side)",
                    accelerator: "B",
                    click: function () {
                        mainWindow.webContents.send("chess", "newGameBlack");
                    }
                }, {
                    type: 'separator'
                }, {
                    label: "Go Back",
                    accelerator: "Backspace",
                    click: function () {
                        mainWindow.webContents.send("chess", "goBack");
                    }
                }, {
                    type: 'separator'
                }, {
                    label: "Quit",
                    accelerator: "Q",
                    click: function () {
                        mainWindow.close();
                    }
                }
            ],
        }, {
            label: "Chess Board",
            submenu: [
                {
                    label: "Small",
                    accelerator: "1",
                    type: 'radio',
                    checked: config.size === 1,
                    click: function () {
                        config.size = 1;
                        changeWindowSize();
                    }
                }, {
                    label: "Middle",
                    accelerator: "2",
                    type: 'radio',
                    checked: config.size === 2,
                    click: function () {
                        config.size = 2;
                        changeWindowSize();
                    }
                }, {
                    label: "Large",
                    accelerator: "3",
                    type: 'radio',
                    checked: config.size === 3,
                    click: function () {
                        config.size = 3;
                        changeWindowSize();
                    }
                }, {
                    type: 'separator'
                }, {
                    label: "Classic Theme",
                    accelerator: "C",
                    type: 'radio',
                    checked: config.theme === "classic",
                    click: function () {
                        config.theme = "classic";
                        changeTheme();
                    }
                }, {
                    label: "Dark Theme",
                    accelerator: "D",
                    type: 'radio',
                    checked: config.theme === "dark",
                    click: function () {
                        config.theme = "dark";
                        changeTheme();
                    }
                }
            ]
        }, {
            label: "Help",
            submenu: [
                {
                    label: "About",
                    accelerator: "F1",
                    click: function () {
                        mainWindow.webContents.send("chess", "about");
                    }
                }
            ]
        }
    ]);
    electron.Menu.setApplicationMenu(menu);
}

electron.ipcMain.on('confirmDialog', function (e, message, callback) {
    const options = {
        type: 'info',
        title: "Chinese Chess Game",
        message: message,
        buttons: ['取消', '确定']
    }
    electron.dialog.showMessageBox(mainWindow, options).then(
        function (index) {
            e.sender.send(callback, index);
        }
    );
});

electron.ipcMain.on('infoDialog', function (e, message) {
    const options = {
        type: 'info',
        title: "Chinese Chess Game",
        message: message,
        buttons: ['确定']
    }
    electron.dialog.showMessageBox(mainWindow, options).then(() => {
    });
});

function createWindow() {
    loadConfig();
    const size = getWindowSizeConfig();
    const bgcolor = themes[config.theme].background;

    // Create the browser window.
    mainWindow = new BrowserWindow({
        width: size[0],
        height: size[1],
        resizable: false,
        backgroundColor: bgcolor,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule: true,
            contextIsolation: false,
        }
    });

    createMenu();

    mainWindow.loadFile(path.join(__dirname, 'index.html')).then(() => {
    });

    mainWindow.on('closed', function () {
        mainWindow = null
    });

    // DEVTOOLS
    // mainWindow.toggleDevTools();
}

app.whenReady().then(() => {
    createWindow()
})

// Quit when all windows are closed.
app.on('window-all-closed', function () {
    saveConfig();
    app.quit()
});
