// viajes.js

// We include the necessary library.
// Se incluye la librería necesaria.
const mysql = require("../database/db");

// We define the function that allows to insert a new trip.
// Se define la funcion que permite insertar un nuevo viaje.
function insertViaje(req,res){
    var sql = 'INSERT INTO viaje (id_camion, fecha_inicio, fecha_final) values (?,?,?)';
    var id_camion = req.body.id_camion;
    var fecha_inicio = req.body.fecha_inicio;
    var fecha_final = req.body.fecha_final;
    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;
        var params = [id_camion,fecha_inicio,fecha_final]; 
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

// We define the function that allows to obtain all the trips.
// Se define la funcion que permite obtener todos los viajes.
function getViajes(req,res){
    var sql = 'SELECT * FROM viaje;';
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

// We define the function that allows to obtain all the readings of a specific trip.
// Se define la funcion que permite obtener todas las lecturas de un viaje específico.
function getViajesYLecturas(req,res){
    var sql = 'SELECT l.*, s.tipo AS sensor_tipo, c.chofer, v.fecha_inicio, v.fecha_final FROM lectura AS l JOIN sensor AS s ON l.id_sensor = s.id_sensor JOIN camion AS c ON s.id_camion = c.id_camion JOIN viaje AS v ON c.id_camion = v.id_camion WHERE v.id_viaje = ?;';
    var id_viaje = req.body.id_viaje;
    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;
        var params = [id_viaje];
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

// We define the function that allows to obtain all the irregular readings of a specific trip.
// Se define la funcion que permite obtener todas las lecturas que sean irregulares de un viaje específico.
function getViajesYLecturasIrregulares(req,res){
    var sql = 'SELECT l.valor AS dato, s.tipo AS sensor, c.chofer, c.matricula AS camion, v.fecha_inicio, v.fecha_final, l.fecha AS momento_registro FROM lectura AS l JOIN sensor AS s ON l.id_sensor = s.id_sensor JOIN camion AS c ON s.id_camion = c.id_camion JOIN viaje AS v ON c.id_camion = v.id_camion WHERE v.id_viaje = 1 AND l.status = "Irregular";';
    var id_viaje = req.body.id_viaje;
    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;
        var params = [id_viaje];
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

// We export the functions.
// Se exportan las funciones.
module.exports = {getViajes, getViajesYLecturas,getViajesYLecturasIrregulares,insertViaje};