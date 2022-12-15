#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include <wiringPi.h>
#include <lcd.h>

#define LCD_RS  13               //Register select pin
#define LCD_E   18               //Enable Pin
#define LCD_D4  21               //Data pin D4
#define LCD_D5  24               //Data pin D5
#define LCD_D6  26               //Data pin D6
#define LCD_D7  27               //Data pin D7

int lcd;

#define BUTTON_1 19
#define BUTTON_2 23
#define BUTTON_3 25

#define BROKER_ADDRESS     "tcp://10.0.0.101:1883"
#define USERNAME "aluno"
#define PASSWORD "@luno*123"

#define CLIENTID    "R-TP04/G03"
#define QOS1         1
#define QOS2         2
#define TIMEOUT     5000L

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

// Definições dos endereços dos sensores digitais
#define SENSOR_D0 "D0"
#define SENSOR_D1 "D1"
#define SENSOR_D2 "D2"
#define SENSOR_D3 "D3"
#define SENSOR_D4 "D4"
#define SENSOR_D5 "D5"
#define SENSOR_D6 "D6"
#define SENSOR_D7 "D7"

volatile MQTTClient_deliveryToken deliveredtoken;
MQTTClient client;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
        printf("-------------MENU-----------\n\n");
        printf("1 - ACENDER LED\n");
        printf("2 - APAGAR LED\n");
        printf("3 - Sensor Analogico\n");
        printf("4 - Sensor digital D0\n");
        printf("5 - Sensor digital D1\n");
        printf("8 - Sair\n");
    wiringPiSetup();
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7,0,0,0,0);
    char* payload = message->payload;
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    lcdPrintf(lcd, "valor: %s", payload);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConexão perdida\n");
    printf("     cause: %s\n", cause);
}

void send(char* topic, char* payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = payload;
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = QOS2;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    MQTTClient_waitForCompletion(client, token, TIMEOUT);
}

int main(int argc, char* argv[])
{
    wiringPiSetup();
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7,0,0,0,0);

    int rc;
    int ch;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    conn_opts.username = USERNAME;
    conn_opts.password = PASSWORD;

    MQTTClient_create(&client, BROKER_ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

        printf("-------------MENU-----------\n\n");
        printf("1 - ACENDER LED\n");
        printf("2 - APAGAR LED\n");
        printf("3 - Sensor Analogico\n");
        printf("4 - Sensor digital D0\n");
        printf("5 - Sensor digital D1\n");
        printf("8 - Sair\n");

        MQTTClient_subscribe(client, RESPONSE, QOS2);
        MQTTClient_subscribe(client, ANALOG_SENSOR, QOS2);
        MQTTClient_subscribe(client, DIGITAL_SENSOR, QOS2);
    do
    {
        ch = getchar();
        switch(ch){
                case '1':
                        send(REQUEST,SET_ON_NODEMCU_LED);
                        lcdClear(lcd);
                        lcdPuts(lcd,"LED ACESA!");
                        break;
                case '2':
                        send(REQUEST,SET_OFF_NODEMCU_LED);
                        lcdClear(lcd);
                        lcdPuts(lcd,"LED APAGADA!");
                        break;
                case '3':
                        send(REQUEST,GET_ANALOG_INPUT_VALUE);
                        lcdClear(lcd);
                        lcdPuts(lcd, "ANALOGIC: ");
                        break;
                case '4':
                        send(ADDRESS,SENSOR_D0);
                        send(REQUEST,GET_DIGITAL_INPUT_VALUE);
                        break;
                case '5':
                        send(ADDRESS,SENSOR_D1);
                        send(REQUEST,GET_DIGITAL_INPUT_VALUE);
                        break;
        }

    }
        while(ch!='8');
        printf("saindo....\n");
        MQTTClient_disconnect(client, 10000);
        MQTTClient_destroy(&client);
        return rc;
}