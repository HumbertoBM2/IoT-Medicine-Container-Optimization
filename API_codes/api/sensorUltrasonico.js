// sensorUltrasonico.js

// We include the necessary library.
// Se incluye la librería necesaria.
const mysql = require("../database/db");

// We define the function that allows to insert a new reading of an Ultrasonic sensor.
// Se define la funcion que permite insertar una nueva lectura de un sensor de Ultrasonico.
function insertLogUltrasonico(req,res){
  var sql = 'INSERT INTO lectura (valor,unidad,status,fecha,id_sensor) values (?,"cm",?,NOW(),?)';
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

// We define the function that allows to obtain all the readings of an Ultrasonic sensor.
// Se define la funcion que permite obtener todas las lecturas de un sensor de Ultrasonico.
function getLogUltrasonico(req,res){
    var sql = 'SELECT l.* FROM lectura l JOIN sensor s ON l.id_sensor = s.id_sensor WHERE s.tipo = "Ultrasonico";';
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

// We define the function that allows to obtain all the readings of an Ultrasonic sensor that are irregular.
// Se define la funcion que permite obtener todas las lecturas de un sensor de Ultrasonico que sean irregulares.
function getLogUltrasonicoIrregular(req,res){
    var sql = 'SELECT l.* FROM lectura AS l JOIN sensor AS s ON l.id_sensor = s.id_sensor WHERE s.tipo = "Ultrasonico" AND l.status = "Irregular";';
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

// We define the function that allows to obtain all the readings of an Ultrasonic sensor that are between two dates.
// Se define la funcion que permite obtener todas las lecturas de un sensor de Ultrasonico que estén entre dos fechas.
function getUltrasonicoLogByDateBetween(req,res){
  var sql = 'SELECT l.* FROM lectura l JOIN sensor s ON l.id_sensor = s.id_sensor WHERE s.tipo = "Ultrasonico" AND fecha between ? and ?';
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

// We export the functions so that they can be used by other files.
// Se exportan las funciones para que puedan ser usadas por otros archivos.
module.exports = {insertLogUltrasonico, getLogUltrasonico,getUltrasonicoLogByDateBetween,getLogUltrasonicoIrregular};