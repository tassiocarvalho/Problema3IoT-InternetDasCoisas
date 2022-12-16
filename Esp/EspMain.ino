#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>


#ifndef STASSID
#define STASSID "INTELBRAS"
#define STAPSK  "Pbl-Sistemas-Digitais"
#endif

//Constantes e variaveis
const char* ssid = STASSID;
const char* password = STAPSK;

const char* mqtt_server = "10.0.0.101";
const char *mqtt_username = "aluno";
const char *mqtt_password = "@luno*123";

String address = "D0";
// Comandos de resposta

#define ANALOG_INPUT_VALUE "0x01"
#define DIGITAL_INPUT_VALUE "0x02"
#define LED_ON "0x03"
#define LED_OFF "0x04"
#define NODE_OK "0x200"

// Comandos de requisição
#define GET_ANALOG_INPUT_VALUE "0x04"
#define GET_DIGITAL_INPUT_VALUE "0x05"
#define SET_ON_NODEMCU_LED "0x06"
#define SET_OFF_NODEMCU_LED "0x07"
#define GET_NODE_CONNECTION_STATUS "0x08"

// Definições dos tópicos
#define ANALOG_SENSOR "leds/sensor-analogico"
#define DIGITAL_SENSOR "leds/sensor-digital"
#define REQUEST "leds/request"
#define RESPONSE "leds/response"
#define ADDRESS "leds/endereco"
#define NODE_CONNECTION_STATUS "leds/status"

// Endereço pino

#define SENSOR_D0 "D0"
#define SENSOR_D1 "D1"
#define SENSOR_D2 "D2"
#define SENSOR_D3 "D3"
#define SENSOR_D4 "D4"
#define SENSOR_D5 "D5"
#define SENSOR_D6 "D6"
#define SENSOR_D7 "D7"

WiFiClient espClient;
PubSubClient MQTT(espClient);

void connectWifi_OTA(){
  Serial.begin(9600);
  delay(10);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();}

  ArduinoOTA.setHostname("ESP-10.0.0.108");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect_MQTT(){
  Serial.print("Attempting MQTT connection...");
  String clientId = "TP04/G01";
  if (MQTT.connect(clientId.c_str(),mqtt_username,mqtt_password)) {
    Serial.println("connected");
    MQTT.subscribe(REQUEST);
    MQTT.subscribe(ADDRESS);
    MQTT.publish(RESPONSE,"node conectada");
  } else {
    Serial.print("failed, rc=");
    Serial.print(MQTT.state());
    Serial.println(" try again in 5 seconds");
    delay(2000);
  }
}

void receivePackage(char* topic, byte* payload, unsigned int length) {
  String msg;

  //obtem a string do payload recebido
  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    msg += c;
  }

  if (strcmp(topic, REQUEST) == 0) {

    if (msg == SET_ON_NODEMCU_LED) {
      digitalWrite(LED_BUILTIN, LOW);
      MQTT.publish(RESPONSE, LED_ON);
    } else if (msg == SET_OFF_NODEMCU_LED) {
      digitalWrite(LED_BUILTIN, HIGH);
      MQTT.publish(RESPONSE, LED_OFF);
    } else if (msg == GET_NODE_CONNECTION_STATUS) {
      MQTT.publish(NODE_CONNECTION_STATUS,NODE_OK);
    } else if (msg == GET_DIGITAL_INPUT_VALUE) {
      getDigitalValue(address);
    } else if (msg == GET_ANALOG_INPUT_VALUE){
      getAnalogValue();
    }
  } else if (strcmp(topic, ADDRESS) == 0) {
      address = msg;
  }

  Serial.print("Mensagem recebida: ");
  Serial.println(msg);
  Serial.println();
}

void getDigitalValue(String addr) {
  int value;
  char buf[4];
  if (addr == "D0") {
    value = digitalRead(D0);
    snprintf(buf,4,"%ld",value);
    MQTT.publish(DIGITAL_SENSOR, buf);
  } else if (addr == "D1") {
    value = digitalRead(D1);
    snprintf(buf,4,"%ld",value);
    MQTT.publish(DIGITAL_SENSOR, buf);
  } else if (addr == "D2") {
    value = digitalRead(D2);
    snprintf(buf,4,"%ld",value);
    MQTT.publish(DIGITAL_SENSOR, buf);
  } else if (addr == "D3") {
    value = digitalRead(D3);
    snprintf(buf,4,"%ld",value);
    MQTT.publish(DIGITAL_SENSOR, buf);
  } else if (addr == "D4") {
    value = digitalRead(D4);
    snprintf(buf,4,"%ld",value);
    MQTT.publish(DIGITAL_SENSOR, buf);
  } else if (addr == "D5") {
    value = digitalRead(D5);
    snprintf(buf,4,"%ld",value);
    MQTT.publish(DIGITAL_SENSOR, buf);
  } else if (addr == "D6") {
    value = digitalRead(D6);
    snprintf(buf,4,"%ld",value);
    MQTT.publish(DIGITAL_SENSOR, buf);
  } else if (addr == "D7") {
    value = digitalRead(D7);
    snprintf(buf,4,"%ld",value);
    MQTT.publish(DIGITAL_SENSOR, buf);
  }
}

void getAnalogValue() {
    int value = analogRead(A0);
    char buf[5];
    snprintf(buf,5,"%ld",value);
    MQTT.publish(ANALOG_SENSOR, buf);
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  connectWifi_OTA();
  MQTT.setServer(mqtt_server, 1883);
  MQTT.setCallback(receivePackage);
  
}

void loop() {
  if(!MQTT.connected()){
    reconnect_MQTT();
  }
  ArduinoOTA.handle();
  MQTT.loop();
}



















