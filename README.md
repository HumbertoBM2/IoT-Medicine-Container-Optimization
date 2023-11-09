# IoT Medicine Container Optimization
 Open-source IoT solution for pharmaceutical supply chains. Ensures safe medicine transport using NodeMCU8266 modules, an API, and real-time monitoring.

## Overview
This project aims to implement IoT to condition a container used for transporting medicines. It seeks to incorporate 5 sensors and 5 actuators that will monitor the container in real-time. These sensors and actuators are controlled using Node MCU 8266 modules. The monitoring data collected is sent to a MySQL-hosted database through an API developed with Node.js.

### Components Used

#### Sensors:
- CO2 Sensor (MQ135)
- Humidity Sensor (DHT11)
- Temperature Sensor (DHT11)
- Motion Sensor (PIR)
- Distance Sensor (HC-SR04)

#### Actuators:
- Solenoid Valve (110 V AC)
- Dual-Channel Relay
- 4 LEDs

The actuators are programmed to perform specific actions when irregular readings are detected.

With this implementation, the project aims to expand transportation options for pharmaceutical and other high-value product supply chains that require specific travel conditions. This solution can help reduce costs by avoiding the need to transport products by air, enabling the transportation of conditioned containers in cargo ship freight.


## Instructions for the API 
### Prerequisites:
- Install MySQL
- Have Node.js and npm installed

### Configuration Steps:
1. Clone this repository using the following command:
```bash
git clone https://github.com/HumbertoBM2/IoT-Medicine-Container-Optimization
```
2. Once the repository is cloned, navigate to the created directory using your terminal. Please note that the `node_modules` directory will be empty and will be populated automatically once the project is initialized with Node.js and the necessary dependencies are added.

3. Initialize the project with the following command:
```bash
npm init
```
Configure the options according to your needs. For casual use, you can skip the configuration by pressing "Enter."

4. Install the necessary dependencies with the following commands:
```bash
npm install express
npm install cors
npm install mysql2
npm install body-parser
npm install -g nodemon
```
5. After following the above steps, the `node_modules` directory should be populated with the necessary content.

6. Before starting the API, you need to create the database where the readings will be stored. To do this, run the SQL script from the repository called `SQL_Script_For_The_DB.sql` using MySQL Workbench or DBeaver.

7. Once the database is ready, return to the project directory using the terminal and start the API with the following command:
```bash
node app.js
```
8. The API should start without any issues. You can now verify its functionality by accessing any of the 33 available endpoints using Postman or a web browser (Firefox is recommended).
## Instructions for the Node modules

### Prerequisites:
- Have a minimum of 1 NodeMCU8266 module (preferably 5).
- Acquire the sensors and actuators mentioned earlier.
- Install Arduino IDE.
- Install the NodeMCU8266 board driver.
- Install the necessary libraries: `ArduinoJson.h`, `MQ135.h`, `DHT.h`, and the internet connection libraries that come with the NodeMCU8266 driver (`ESP8266WiFi.h` and `ESP8266HTTPClient.h`).
- Ensure access to a Wi-Fi network that your computer hosting the API and the NodeMCU8266 modules can connect to.

### Configuration:
1. Set up the necessary circuits to connect the NodeMCU8266 module(s), sensors, and actuators. Document the pins used for each component.
2. Open the 5 `.ino` files from the repository and adjust the pin configurations in each code according to your setup.
3. In each .ino file, specify the SSID and password of the Wi-Fi network that the modules will connect to (it should be the same network as the one your computer hosting the API is connected to).
4. Obtain the IPv4 address of your computer by running the following command in the terminal:
```bash
ipconfig
```

5. Replace the IP address in all the endpoints within the 5 code files.
6. Ensure that the IDs to which each reading will be sent are appropriate for your needs, although you can leave the default values if they suffice.
7. Upload the code to the NodeMCU8266 modules.
8. Open the serial monitor and observe how POST requests are generated as the environment is read.
9. Confirm that the data is being loaded into the database by using one of the GET endpoints.

You are now ready to set up and use the NodeMCU8266 modules in conjunction with the IoT solution.
