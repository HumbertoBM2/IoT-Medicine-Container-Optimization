// codigoSensorCo2IoT.ino

// Include the libraries we need
// Librerias necesarias
#include <MQ135.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// We define the CO2 sensor pin
// Pin para el sensor de CO2
const int analogPin = A0; 
// Pin for the actuator D1 
// Pin para el actuador D1
const int actuador = 5; 
// Average PPM 
// Promedio de PPM
const float thresholdPPM = 1000;  

// Declare an object of type MQ135 and we assign an analog reading to the pin for the sensor
// Se declara un objeto de tipo MQ135
// Se le asigna una lectura analoga al pin para el sensor
MQ135 gasSensor(analogPin); 

// We define the IP of the server and the port
// Se define el IP del servidor y el puerto
#define SERVER_IP "000.000.000.000:3000" // Replace with your IP and port

// We define the ssid and password of the network to use
// Se define el ssid y la contraseña de la red a usar
#ifndef STASSID
#define STASSID "ssid" // Replace with your SSID
#define STAPSK "password" // Replace with your Password
#endif

// Setup
void setup() {

  // Begin serial communication
  // Inicar comunicación serial
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();

  // Start internet connection
  // Arrancar conexion a internet
  WiFi.begin(STASSID, STAPSK);

  // Wait for connection
  // Verificar que la conexion haya sido exitosa
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Show assigned IP
  // Mostrar IP asignada 
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  
}

// loop
void loop() {
  
  // Code to get readings and control the solenoid valve
  // Codigo para obtener lecturas y controlar la válvula solenoide
  // Se declara como valor flotante la lectura del sensor
  float lectura = gasSensor.getPPM(); 
  // Print the measurement with its respective units (Parts per million)
  // Se imprime la medicion con sus respectivas unidades (Parts per million)
  Serial.print("Concentracion de gas (PPM): "); 
  Serial.println(lectura);
  // Validate if the readings are abnormal according to the average PPM reference
  // Validar si las lecturas son anormales segun la referencia de PPM promedio
  if (lectura < thresholdPPM) {
    digitalWrite(actuador, HIGH);  // Encender el actuador cuando la lectura sea anormal
  } else {
    digitalWrite(actuador, LOW);   // Encender el actuador cuando la lectura sea normal
  }
  delay(10000);

  // Code to insert the reading in the DB
  // Codigo para insertar la lectura en la BD

  // Wait for internet connection
  // Esperar por conexion a internet
  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    // Define endpoint for inserting sensor readings
    // Definir endpoint para la insercion de las lecturas del sensor
    http.begin(client, "http://000.000.000.000:3000/api/insertLogCO2"); // Replace with your IP and port
    // Define the header to use for requests
    // Definir el header a usar para las solicitudes
    http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] POST...\n");
    // Define the body of the request based on whether the reading was normal or abnormal
    // Definir el cuerpo de la solicitud con base a si la lectura fue normal o anormal
    if (lectura < thresholdPPM){
      StaticJsonDocument<64> doc;
      doc["valor"] = lectura;
      doc["status"] = "Regular";
      doc["id_sensor"] = 1; // Ajustar segun el sensor de donde se este obteniendo la lectura / Adjust according to the sensor from which the reading is being obtained
      // Serialize the JSON object to a string
      // Serializar el objeto JSON a una cadena
      String jsonString;
      serializeJson(doc, jsonString);
      // Print the string to the serial monitor
      // Imprimir la cadena en el monitor serial
      Serial.println(jsonString);
      // Make the POST request to the API
      // Hacer la solicitud POST a la API
      int httpCode = http.POST(jsonString);
      // Verify that the API response code does not correspond to an error
      // Verificar que el codigo de respuesta de la API no corresponda a un error
      if (httpCode > 0) {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
          const String& payload = http.getString();
          Serial.println("received payload:\n<<");
          Serial.println(payload);
          Serial.println(">>");
        }
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
    } else {
      StaticJsonDocument<64> doc;
      doc["valor"] = lectura;
      doc["status"] = "Irregular";
      doc["id_sensor"] = 1; // Ajustar segun el sensor de donde se este obteniendo la lectura / Adjust according to the sensor from which the reading is being obtained
      // Serialize the JSON object to a string
      // Serializar el objeto JSON a una cadena
      String jsonString;
      serializeJson(doc, jsonString);
      // Print the string to the serial monitor
      // Imprimir la cadena en el monitor serial
      Serial.println(jsonString);
      // Make the POST request to the API
      // Hacer la solicitud POST a la API
      int httpCode = http.POST(jsonString);
      // Verify that the API response code does not correspond to an error
      // Verificar que el codigo de respuesta de la API no corresponda a un error
      if (httpCode > 0) {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
          const String& payload = http.getString();
          Serial.println("received payload:\n<<");
          Serial.println(payload);
          Serial.println(">>");
        }
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
    }
    // End connection when request is finished
    // Terminar conexion cuando se termine la solicitud
    http.end();
  }
  delay(10000);
  
}
