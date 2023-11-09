// codigoSensorMovIoT.ino

// Include the libraries we need
// Librerias necesarias
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// We define the LED pin
// Definimos el pin al que está conectado el LED
int Status = 12; 

// We define a variable 'sensor' that stores the pin number to which the motion sensor is connected.
// Definimos una variable 'sensor' que almacena el número del pin al que está conectado el sensor de movimiento.
int sensor = 14;

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
  
  // We configure the 'sensor' pin as an input, indicating that this pin is connected to the motion sensor.
  // Configuramos el pin 'sensor' como entrada, indicando que este pin está conectado al sensor de movimiento.
  pinMode(sensor, INPUT);
  
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
  // Leemos el estado del pin 'sensor' y lo almacenamos en la variable 'state'.
  long state = digitalRead(sensor);
  // Hacemos una pausa de 500 milisegundos.
  delay(500);
  // We check if the state of the sensor is high, which indicates motion detection.
  // Comprobamos si el estado del sensor es alto, lo que indica detección de movimiento.
  if (state == HIGH) {
    // We turn on the LED or perform the action corresponding to the detection state.
    // Encendemos el LED o realizamos la acción correspondiente al estado de detección.
    digitalWrite(Status, HIGH);
    Serial.println("Motion detected!");
  } else {
    // We turn off the LED or perform the action corresponding to the non-detection state.
    // Apagamos el LED o realizamos la acción correspondiente al estado de no detección.
    digitalWrite(Status, LOW);
    Serial.println("Motion absent!");
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
    http.begin(client, "http://000.000.000.000:3000/api/insertLogMov");  // Replace with your IP and port
    // Define the header to use for requests
    // Definir el header a usar para las solicitudes
    http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] POST...\n");
    // Define the body of the request based on whether the reading was normal or abnormal
    // Definir el cuerpo de la solicitud con base a si la lectura fue normal o anormal
    if (state == HIGH){
      StaticJsonDocument<64> doc;
      doc["valor"] = 1;
      doc["status"] = "Irregular";
      doc["id_sensor"] = 4; // Ajustar segun el sensor de donde se este obteniendo la lectura / Adjust according to the sensor from which the reading is being obtained
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
      doc["valor"] = 0;
      doc["status"] = "Regular";
      doc["id_sensor"] = 4; // Ajustar segun el sensor de donde se este obteniendo la lectura / Adjust according to the sensor from which the reading is being obtained
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
