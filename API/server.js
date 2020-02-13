const express = require('express');
const app = express();
const path = require('path');
const router = express.Router();
const port = 8080;

//Libreria con las funcionalidades de base de datos
const bd = require('./mongo.js');

app.use(express.static('frontend'));

/*
Importante: al retornar valores a una petición desde arduino, es importante que los datos retornados sean un string
            esto para evitar convertir respuestas JSON desde el microcontrolador, que es tedioso y muy específico. 

            Para separar los valores, la convención que utilizaremos es $NOMBRE_valor_NOMBRE$ si se debe retornar más de un valor,
            de lo contrario solamente el valor. De esta manera será fácil realizar un split de los valores desde arduino, y/o posteriormente un cast. 
*/

//Variable donde se almacenaran todas las palabras
let words = [];

//Mensajes para frontend
let NO_WRD_MESSAGE = "No se envió ninguna palabra.";
let WRD_ADDED = "Palabra agregada.";
let NO_WRD_REMAINING = "No existen más palabras en la cola.";
let DB_ERROR = "No se guardó la palabra, error en la base de datos.";
let DB_ERROR2 = "No se pudo retornar las palabras dela base de datos.";

//función para comprobar si la petición es desde el dispositivo arduino.
let isArduino = function(req){
    return req.query != null && req.query.arduino == "true";
};

//Agregar una palabra a la cola de palabras
app.get("/addWord", (req, res) => {

    let arduino = isArduino(req);

    //Revisar si la palabra viene adjunta en el request
    if (!req.query || !req.query["word"]){
        //Enviar mensaje de error, y el codigo 0 que indica error.
        return arduino ? 
            res.send(NO_WRD_MESSAGE) : 
            res.status(401).json({ msg: NO_WRD_MESSAGE, status: 0, added_word: null});
    }

    //agregar palabra a la cola
    let word = req.query["word"];
    words.push(word);

    bd.saveWord({ word: word, typedIn: isArduino(req) ? "arduino" : "web"}, function(err){
        if (err){
            //Si ocurrió un error al agregar la palabra a la base de datos
            return arduino ?
                res.send(DB_ERROR) :
                res.status(500).json({msg: DB_ERROR, status: 0, added_word: null}); 
        }
        
        //Retornar confirmación de palabra agregada
        return arduino ? 
            res.send(`Palabra ${word} agregada`) :
            res.json({ msg: WRD_ADDED, status: 1, added_word: word});
    });
});

//Agregar una palabra a la cola de palabras
app.get("/getListWords", (req, res) => {
    bd.getWords((err, words) => {
        if (err){
            //Si ocurrió un error al agregar la palabra a la base de datos
            return res.status(500).json({msg: DB_ERROR2, status: 0, error: err}); 
        }
        
        //Retornar confirmación de palabra agregada
        return res.json(words);
    });
});

//Obtener la primera palabra agregada que no ha sido obtenida antes
app.get("/getWord", (req, res) => {
    //Si no hay mas palabras en la cola
    if (words.length < 1){
        return isArduino(req) ? 
            res.send(NO_WRD_REMAINING) :
            res.json({ msg: NO_WRD_REMAINING, status: 1, word: null});
    }
    //Obtener la primera palabra de la cola, y eliminarla
    let current_word = words.shift();

    return isArduino(req) ? 
        res.send(current_word) :
        res.json({ word: current_word });
});

//Funcion que retorna la página de la aplicación
app.get("/", (req, res) => {
    return res.sendFile(path.join(__dirname + '/frontend/index.html'));
});

//Iniciar la aplicación
app.listen(port, () => console.log(`Aplicación iniciada en el puerto ${port}...`));