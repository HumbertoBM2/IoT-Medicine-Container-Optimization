// codigoSensorUltrasonicoIoT.ino

// Include the libraries we need
// Librerias necesarias
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
 
 // We define the pin connections of the HC-SR04 ultrasonic sensor
// Definimos las conexiones de los pines del sensor ultrasónico HC-SR04
// Trigger pin
// Pin de disparo
const int trigPin = 3; 
// Echo pin
// Pin de eco
const int echoPin = 2; 
// Pin of the LED integrated in the Arduino board
// Pin del LED integrado en la placa Arduino
const int ledPin = LED_BUILTIN; 

// We define the speed of sound in cm/us (microseconds)
// Definimos la velocidad del sonido en cm/us (microsegundos)
#define SOUND_VELOCITY 0.034 

// We define a conversion factor from centimeters to inches
// Definimos un factor de conversión de centímetros a pulgadas
#define CM_TO_INCH 0.393701

// Variables to store the time it takes for the signal to return and the calculated distances
// Variables para almacenar el tiempo que la señal tarda en regresar y las distancias calculadas
long duration;
float distanceCm;
float distanceInch;
const float test = 20; // Distancia de prueba (en cm) // Test distance (in cm)

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
  // We set the trigger pin (trigPin) as output
  // Configuramos el pin de disparo (trigPin) como salida
  pinMode(trigPin, OUTPUT); 
  // We set the echo pin (echoPin) as input
  // Configuramos el pin de eco (echoPin) como entrada
  pinMode(echoPin, INPUT); 

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
  // Ponemos el trigPin en estado bajo para asegurarnos de que esté limpio
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  // Activate the trigPin in high state for 10 microseconds to send an ultrasonic pulse
  // Activamos el trigPin en estado alto durante 10 microsegundos para enviar un pulso ultrasónico
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the time it takes for the ultrasonic pulse to bounce and return
  // Leemos el tiempo que tarda el pulso ultrasónico en rebotar y regresar
  duration = pulseIn(echoPin, HIGH);
  // We calculate the distance using the formula: distance = (time x sound speed) / 2
  // Calculamos la distancia usando la fórmula: distancia = (tiempo x velocidad del sonido) / 2
  distanceCm = duration * SOUND_VELOCITY / 2;
  // We convert the distance from centimeters to inches
  // Convertimos la distancia de centímetros a pulgadas
  distanceInch = distanceCm * CM_TO_INCH;
  
  // If the distance is less than the test value (20 cm in this case), we turn on the integrated LED
  // Si la distancia es menor que el valor de prueba (20 cm en este caso), encendemos el LED integrado
  if (distanceCm < test){
    digitalWrite(ledPin, HIGH); // Lectura anormal // Abnormal reading
  } else {
    digitalWrite(ledPin, LOW); // Lectura normal // Normal reading
  }
  // We print the distance in centimeters on the Serial Monitor
  // Imprimimos la distancia en centímetros en el Monitor Serie
  Serial.print("Distancia (cm): ");
  Serial.println(distanceCm);

  
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
    http.begin(client, "http://000.000.000.000:3000/api/insertLogUltrasonico");  // Replace with your IP and port
    // Define the header to use for requests
    // Definir el header a usar para las solicitudes
    http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] POST...\n");
    // Define the body of the request based on whether the reading was normal or abnormal
    // Definir el cuerpo de la solicitud con base a si la lectura fue normal o anormal
    if (distanceCm < test){
      StaticJsonDocument<64> doc;
      doc["valor"] = distanceCm;
      doc["status"] = "Irregular";
      doc["id_sensor"] = 5; // Ajustar segun el sensor de donde se este obteniendo la lectura / Adjust according to the sensor from which the reading is being obtained
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
      doc["valor"] = distanceCm;
      doc["status"] = "Regular";
      doc["id_sensor"] = 5; // Ajustar segun el sensor de donde se este obteniendo la lectura / Adjust according to the sensor from which the reading is being obtained
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
    // End connection when the request is finished
    // Terminar conexion cuando se termine la solicitud
    http.end();
  }
  delay(10000);
  
}
