// lecturas.js

// We include the necessary library.
// Se incluye la librería necesaria.
const mysql = require("../database/db");

// We define the function that allows to obtain all the readings.
// Se define la funcion que permite obtener todas las lecturas.
function getLecturas(req,res){
    var sql = 'SELECT * FROM lectura;';
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

// We define the function that allows to obtain all the readings that are irregular.
// Se define la funcion que permite obtener todas las lecturas que sean irregulares.
function getLecturasIrregulares(req,res){
    var sql = 'SELECT * FROM lectura WHERE status = "Irregular";';
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

// We define the function that allows to obtain all the readings of a specific truck.
// Se define la funcion que permite obtener todas las lecturas de un camión específico.
function getLecturasPorCamion(req,res){
  var sql = 'SELECT l.* FROM lectura AS l JOIN sensor AS s ON l.id_sensor = s.id_sensor JOIN camion AS c ON s.id_camion = c.id_camion WHERE c.id_camion = ?;';
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

// We define the function that allows to obtain all the readings in a range of dates.
// Se define una funcion que permite obtener todas las lecturas en un rango de fechas.
function getLecturasByDateBetween(req,res){
    var sql = 'SELECT * FROM lectura WHERE fecha between ? and ?';
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
module.exports = {getLecturas, getLecturasPorCamion, getLecturasByDateBetween,getLecturasIrregulares};