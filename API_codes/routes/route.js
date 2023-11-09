// route.js

// We include the necessary libraries.
// Se incluyen las librerías necesarias.
const express = require('express');
// We include the controllers.
// Se incluyen los controladores.
const co2Controller = require('../api/sensorCO2.js'); 
const tempController = require('../api/sensorTemp.js');
const humedadController = require('../api/sensorHumedad.js');
const movController = require('../api/sensorMov.js');
const ultrasonicoController = require('../api/sensorUltrasonico.js');
const sensoresController = require('../api/sensores.js');
const lecturasController = require('../api/lecturas.js');
const camionesController = require('../api/camiones.js');
const viajesController = require('../api/viajes.js');
// We create an instance of express.
// Se crea una instancia de express.
const router = express.Router();

// We define the endpoints for the CO2 sensor.
// Se definen los endpoints para el sensor de CO2.
router.get('/api/getLogCO2', co2Controller.getLogCO2);
router.get('/api/getCO2LogByDateBetween', co2Controller.getCO2LogByDateBetween);
router.get('/api/getLogCO2Irregular', co2Controller.getLogCO2Irregular);
router.post('/api/insertLogCO2', co2Controller.insertLogCO2);
// We define the endpoints for the Temperature sensor.
// Se definen los endpoints para el sensor de Temperatura.
router.get('/api/getLogTemp', tempController.getLogTemp);
router.get('/api/getTempLogByDateBetween', tempController.getTempLogByDateBetween);
router.get('/api/getLogTempIrregular', tempController.getLogTempIrregular);
router.post('/api/insertLogTemp', tempController.insertLogTemp);
// We define the endpoints for the Humidity sensor.
// Se definen los endpoints para el sensor de Humedad.
router.get('/api/getLogHumedad', humedadController.getLogHumedad);
router.get('/api/getHumedadLogByDateBetween', humedadController.getHumedadLogByDateBetween);
router.get('/api/getLogHumedadIrregular', humedadController.getLogHumedadIrregular);
router.post('/api/insertLogHumedad', humedadController.insertLogHumedad);
// We define the endpoints for the Movement sensor.
// Se definen los endpoints para el sensor de Movimiento.
router.get('/api/getLogMov', movController.getLogMov);
router.get('/api/getMovLogByDateBetween', movController.getMovLogByDateBetween);
router.get('/api/getLogMovIrregular', movController.getLogMovIrregular);
router.post('/api/insertLogMov', movController.insertLogMov);
// We define the endpoints for the Ultrasonic sensor.
// Se definen los endpoints para el sensor de Ultrasonico.
router.get('/api/getLogUltrasonico', ultrasonicoController.getLogUltrasonico);
router.get('/api/getUltrasonicoLogByDateBetween', ultrasonicoController.getUltrasonicoLogByDateBetween);
router.get('/api/getLogUltrasonicoIrregular', ultrasonicoController.getLogUltrasonicoIrregular);
router.post('/api/insertLogUltrasonico', ultrasonicoController.insertLogUltrasonico);
// We define the endpoints for the sensors.
// Se definen los endpoints para los sensores.
router.get('/api/getSensores', sensoresController.getSensores);
router.post('/api/insertNuevoSensor', sensoresController.insertNuevoSensor);
router.get('/api/getSensoresPorCamion', sensoresController.getSensoresPorCamion);
// We define the endpoints for the readings.
// Se definen los endpoints para las lecturas.
router.get('/api/getLecturas', lecturasController.getLecturas);
router.get('/api/getLecturasPorCamion', lecturasController.getLecturasPorCamion);
router.get('/api/getLecturasByDateBetween', lecturasController.getLecturasByDateBetween);
router.get('/api/getLecturasIrregulares', lecturasController.getLecturasIrregulares);
// We define the endpoints for the trucks.
// Se definen los endpoints para los camiones.
router.get('/api/getCamiones', camionesController.getCamiones);
router.post('/api/insertCamion', camionesController.insertCamion);
// We define the endpoints for the trips.
// Se definen los endpoints para los viajes.
router.get('/api/getViajes', viajesController.getViajes);
router.get('/api/getViajesYLecturas', viajesController.getViajesYLecturas);
router.get('/api/getViajesYLecturasIrregulares', viajesController.getViajesYLecturasIrregulares);
router.post('/api/insertViaje', viajesController.insertViaje);
// Export the module.
// Se exporta el módulo.
module.exports = router;