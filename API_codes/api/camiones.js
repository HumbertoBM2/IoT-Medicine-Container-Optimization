// camiones.js

// We include the necessary library.
// Se incluye la librería necesaria.
const mysql = require("../database/db");

// We define the function that allows to insert a new truck.
// Se define la funcion que permite insertar un nuevo camión.
function insertCamion(req,res){
    var sql = 'INSERT INTO camion (chofer, matricula) values (?,?)';
    var chofer = req.body.chofer;
    var matricula = req.body.matricula;
    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;
        var params = [chofer,matricula]; 
        conn.execute(sql, params, (error, data, fields) => {
            if (error) {
              res.status(500);
              res.send(error.message);
            } else {
              console.log(data);
              res.json({
                status: 200,
                message: "Valor insertado",
                affectedRows: data.affectedRows,
              });
            }
            conn.end();
        });
    });
}

// We define the function that allows to obtain all the trucks.
// Se define la funcion que permite obtener todos los camiones.
function getCamiones(req,res){
    var sql = 'SELECT * FROM camion;';
    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;
        conn.query(sql, (error, data, fields) => {
            if (error) {
              res.status(500);
              res.send(error.message);
            } else {
              console.log(data);
              res.json({
                data,
              });
            }
            conn.end();
        });
    });
}

// Export the functions defined.
// Se exportan las funciones definidas.
module.exports = {getCamiones,insertCamion};