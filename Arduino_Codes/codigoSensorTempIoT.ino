// codigoSensorTempIoT.ino

// We include the libraries we need
// Librerias necesarias
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h" 

// We define the DHT 11 type object
// Objeto de tipo DHT 11
#define DHTTYPE DHT11 
// We define the data reception pin as number 5
// Se define el pin de recepción de datos como el número 5
#define dht_dpin 5  

DHT dht(dht_dpin, DHTTYPE);

// We define the LED pin
// Definimos el pin al que está conectado el LED
int Status = 12; 

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

  // We initialize the sensor
  // Se inicializa el sensor
  dht.begin();
  // We configure the 'Status' pin as an output, which will be used to control an LED or other device.
  // Configuramos el pin 'Status' como salida, que se utilizará para controlar un LED u otro dispositivo.
  pinMode(Status, OUTPUT);

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
  
  // Code to get readings and the actuator
  // Codigo para obtener lecturas y el actuador
  // Se leen los datos de humedad del sensor
  float t = dht.readTemperature();
  float tempPromedio = 8;  // Temperatura a la que se almacena la insulina / Temperature at which insulin is stored
  // Print each value along with its unit of measure
  // Se hace la impresión de cada valor junto con su unidad de medida
  Serial.print("Temperatura = ");
  Serial.print(t);
  Serial.print("°C ");
  if (t > tempPromedio){
    digitalWrite(Status, HIGH);  // Se enciende el actuador cuando las lecturas son muy altas / We turn on the actuator when the readings are very high
    Serial.println("Temperatura alta");
  } else {
    digitalWrite(Status, LOW);
    Serial.println("Temperatura normal"); // Se apaga el actuador cuando las lecturas son normales / We turn off the actuator when the readings are normal
  }
  
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
    http.begin(client, "http://000.000.000.000:3000/api/insertLogTemp");  // Replace with your IP and port
    // Define the header to use for requests
    // Definir el header a usar para las solicitudes
    http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] POST...\n");
    // Define the body of the request based on whether the reading was normal or abnormal
    // Definir el cuerpo de la solicitud con base a si la lectura fue normal o anormal
    if (t > tempPromedio){
      StaticJsonDocument<64> doc;
      doc["valor"] = t;
      doc["status"] = "Irregular";
      doc["id_sensor"] = 2; // Ajustar segun el sensor de donde se este obteniendo la lectura / Adjust according to the sensor from which the reading is being obtained
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
      doc["valor"] = t;
      doc["status"] = "Regular";
      doc["id_sensor"] = 2; // Ajustar segun el sensor de donde se este obteniendo la lectura / Adjust according to the sensor from which the reading is being obtained
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
    // End connection when request finishes
    // Terminar conexion cuando se termine la solicitud
    http.end();
  }
  delay(10000);
  
}
