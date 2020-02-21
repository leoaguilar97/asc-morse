const express = require('express');
const app = express();
const path = require('path');
const router = express.Router();
const port = 8080;



app.use(express.static('frontend'));


//Funcion que retorna la página de la aplicación
app.get("/", (req, res) => {
    return res.sendFile(path.join(__dirname + '/frontend/index.html'));
});

app.get("/report", (req, res) => {
    return res.sendFile(path.join(__dirname + '/frontend/report.html'));
});

app.get("/game", (req, res) => {
    return res.sendFile(path.join(__dirname + '/frontend/game.html'));
});

app.get("/message", (req, res) => {
    return res.sendFile(path.join(__dirname + '/frontend/message.html'));
});

//Iniciar la aplicación
app.listen(port, () => console.log(`Aplicación iniciada en el puerto ${port}...`));