
/*
Gestor de base de datos para almacenar y obtener palabras.

Basado en el driver de mongodb para nodejs: mongodb@3.5.3
URI de conexion obtenido de la pagina de MongoAtlas
*/

const MongoClient = require('mongodb').MongoClient;
const uri = "mongodb+srv://leo:leo1234@ascmorsedbc1-2ujtz.gcp.mongodb.net/test?retryWrites=true&w=majority";
const client = new MongoClient(uri, { useNewUrlParser: true });


/*
Función que debe guardar una palabra en la base de datos mongodb, ubicada en un servidor Mongo Atlas
*/
exports.saveWord = function(document, callback){
    //conectar el cliente de MongoDb
    client.connect(err => {
        //Si existió algún error en la conexión
        if (err){
            console.log(">> Error de conexion a bd: ");
            console.log(err);
            return callback(err);
        }

        //Obtener la colección que guardará las palabras, ubicada en la base de datos ascmorse -> words
        const collection = client.db("ascmorse").collection("words");

        //Insertar el objeto
        collection.insertOne(document, (err, res) =>{
            //Si existió algún error en la inserción del dato
            if (err){
                console.log(">> Error al insertar dato: ");
                console.log(err);

                return callback(err);
            }
            
            //El documento fue insertado
            console.log(">> Documento agregado exitosamente");
            client.close();
            callback(null);
        });
    });
}