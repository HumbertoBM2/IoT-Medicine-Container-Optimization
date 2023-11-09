// sensores.js

// We include the necessary libraries.
// Se incluyen las librerías necesarias
const mysql = require("../database/db");

// We define the function that allows to insert a new sensor.
// Se define la función que inserta un nuevo sensor
function insertNuevoSensor(req,res){
  var sql = 'INSERT INTO sensor (tipo, id_camion) values (?,?)';
  var tipo = req.body.tipo;
  var id_camion = req.body.id_camion;
  var conn = mysql.getConnection();
  conn.connect((error)=>{
      if (error) throw error;
      var params = [tipo,id_camion];
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

// We define the function that allows to obtain all the sensors.
// Se define la función que obtiene todos los sensores
function getSensores(req,res){
    var sql = 'SELECT * FROM sensor;';
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

// We define the function that allows to obtain all the sensors of a truck.
// Se define la función que obtiene todos los sensores de un camión
function getSensoresPorCamion(req,res){
  var sql = 'SELECT * FROM sensor WHERE id_camion = ?;';
  var id_camion = req.body.id_camion;
  var conn = mysql.getConnection();
  conn.connect((error)=>{
      if (error) throw error;
      var params = [id_camion];
      conn.execute(sql, params, (error, data, fields) => {
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

// Export the functions
// Se exportan las funciones
module.exports = {insertNuevoSensor, getSensores, getSensoresPorCamion};