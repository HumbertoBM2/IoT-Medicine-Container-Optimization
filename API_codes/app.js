// app.js

// Include libraries needed for the web server.
// Incluir librerías necesarias para el servidor web.
const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const router = require('./routes/route')

// We create an instance of express.
// Se crea una instancia de express.
const app = express();
// We define the port on which the web server will run.
// Se define el puerto en el que correrá el servidor web.
const port = 3000;
// We configure the web server to receive requests from any origin.
// Se configura el servidor web para que pueda recibir peticiones de cualquier origen.
app.use(cors());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.use(router);

// We define the root path of the web server.
// Se define la ruta raíz del servidor web.
app.get('/', (req, res) => {
    res.send('Hello world!')
});
// We start the web server.
// Se inicia el servidor web.
app.listen(port, () => {
    console.log('Server started running on : ' + port)
})