// sensorHumedad.js

// We include the necessary library.
// Se incluye la librería necesaria.
const mysql = require("../database/db");

// We define the function that allows to insert a new reading of a Humidity sensor.
// Se define la funcion que permite insertar una nueva lectura de un sensor de Humedad.
function insertLogHumedad(req,res){
  var sql = 'INSERT INTO lectura (valor,unidad,status,fecha,id_sensor) values (?,"%",?,NOW(),?)';
  var valor = req.body.valor;
  var id_sensor = req.body.id_sensor;
  var status = req.body.status;
  var conn = mysql.getConnection();
  conn.connect((error)=>{
      if (error) throw error;
      var params = [valor,status,id_sensor,]; 
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

// We define the function that allows to obtain all the readings of a Humidity sensor that are irregular.
// Se define la funcion que permite obtener todas las lecturas de un sensor de Humedad que sean irregulares.
function getLogHumedadIrregular(req,res){
    var sql = 'SELECT l.* FROM lectura AS l JOIN sensor AS s ON l.id_sensor = s.id_sensor WHERE s.tipo = "Humedad" AND l.status = "Irregular";';
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

// We define the function that allows to obtain all the readings of a Humidity sensor.
// Se define la funcion que permite obtener todas las lecturas de un sensor de Humedad.
function getLogHumedad(req,res){
    var sql = 'SELECT l.* FROM lectura l JOIN sensor s ON l.id_sensor = s.id_sensor WHERE s.tipo = "Humedad";';
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

// We define the function that allows to obtain all the readings of a Humidity sensor between two dates.
// Se define la funcion que permite obtener todas las lecturas de un sensor de Humedad que estén entre dos fechas.
function getHumedadLogByDateBetween(req,res){
  var sql = 'SELECT l.* FROM lectura l JOIN sensor s ON l.id_sensor = s.id_sensor WHERE s.tipo = "Humedad" AND fecha between ? and ?';
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

// Export the functions.
// Se exportan las funciones.
module.exports = {insertLogHumedad, getLogHumedad,getHumedadLogByDateBetween,getLogHumedadIrregular};