// sensorCO2.js

// We include the necessary library.
// Se incluye la librería necesaria.
const mysql = require("../database/db");

// We define the function that allows to insert a new reading of a CO2 sensor.
// Se define la funcion que permite insertar una nueva lectura de un sensor de CO2.
function insertLogCO2(req,res){
  var sql = 'INSERT INTO lectura (valor,unidad,status,fecha,id_sensor) values (?,"ppm",?,NOW(),?)';
  var valor = req.body.valor;
  var id_sensor = req.body.id_sensor;
  var status = req.body.status;
  var conn = mysql.getConnection();
  conn.connect((error)=>{
      if (error) throw error;
      var params = [valor,status,id_sensor]; 
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

// We define the function that allows to obtain all the readings of a CO2 sensor.
// Se define la funcion que permite obtener todas las lecturas de un sensor de CO2.
function getLogCO2(req,res){
    var sql = 'SELECT l.* FROM lectura l JOIN sensor s ON l.id_sensor = s.id_sensor WHERE s.tipo = "CO2";';
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

// We define the function that allows to obtain all the readings of a CO2 sensor that are irregular.
// Se define la funcion que permite obtener todas las lecturas de un sensor de CO2 que sean irregulares.
function getLogCO2Irregular(req,res){
  var sql = 'SELECT l.* FROM lectura AS l JOIN sensor AS s ON l.id_sensor = s.id_sensor WHERE s.tipo = "CO2" AND l.status = "Irregular";';
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

// We define the function that allows to obtain all the readings of a CO2 sensor that are between two dates.
// Se define la funcion que permite obtener todas las lecturas de un sensor de CO2 que se encuentren entre dos fechas.
function getCO2LogByDateBetween(req,res){
  var sql = 'SELECT l.* FROM lectura l JOIN sensor s ON l.id_sensor = s.id_sensor WHERE s.tipo = "CO2" AND fecha between ? and ?';
  var date_one = req.body.date_one;
  var date_two = req.body.date_two;
  var conn = mysql.getConnection();
  conn.connect((error)=>{
      if (error) throw error;
      var params = [date_one,date_two];
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

// We export the functions to be used in other files.
// Se exportan las funciones para poder ser utilizadas en otros archivos.
module.exports = {insertLogCO2, getLogCO2,getCO2LogByDateBetween,getLogCO2Irregular};