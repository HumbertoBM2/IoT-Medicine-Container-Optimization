// db.js

// We include the necessary library.
// Se incluye la librería necesaria.
const mysql = require('mysql2');

// We define the function that allows to obtain the connection to the database.
// Se define la función que permite obtener la conexión a la base de datos.
function getConnection(){
  const connection = mysql.createConnection({
    host: "host", // Replace with your host name, normally localhost
    user: "root",
    password: "password", // Replace with your MYSQL password
    database: "Unidad_de_Monitoreo" // Use the created database
  });

  return connection;
}

// We export the function.
// Se exporta la función.
module.exports = {getConnection};
