const TOPIC_RESPONSE = "leds/response"
const TOPIC_NODE_CONECTION = "leds/status"
const TOPIC_REQUEST = "leds/request"
const TOPIC_ANALOG_SENSOR = "leds/sensor-analogico"
const TOPIC_DIGITAL_SENSOR = "leds/sensor-digital"

const nodeIndicator = document.getElementById("node-indicator")
const brokerIndicator = document.getElementById("broker-indicator")

let brokerIsConnected = false
let nodeIsConnected = false
let nextStateLed = false

var data = [];

let pahoConfig = {
    hostname: "10.0.0.101",  //The hostname is the url, under which your FROST-Server resides.
    port: 9001,
              //The port number is the WebSocket-Port,
                            // not (!) the MQTT-Port. This is a Paho characteristic.
    clientId: "APP-TP04/G01"    //Should be unique for every of your client connections.
}

let client = new Paho.MQTT.Client(pahoConfig.hostname, Number(pahoConfig.port), pahoConfig.clientId);
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

client.connect({
    userName: "aluno",
    password: "@luno*123", 
    onSuccess: onConnect,
    onFailure:onFailureConnect,
    reconnect:true,
})

function onFailureConnect(){
    console.log("Falha ao tentar se conectar")
}

function onConnect() {
    // Once a connection has been made, make a subscription and send a message.
    console.log("Conexão estabelecida")
    brokerIsConnected = true
    client.subscribe(TOPIC_RESPONSE)
    client.subscribe(TOPIC_NODE_CONECTION)
    setConnectionStatus(brokerIndicator,brokerIsConnected)
    client.send(TOPIC_REQUEST,"0x08")
    client.send(TOPIC_ANALOG_SENSOR, "0x04")
}

function onConnectionLost(responseObject) {
    console.log(responseObject)
    if (responseObject.errorCode !== 0) {
        console.log("onConnectionLost:" + responseObject.errorMessage);
    }
    brokerIsConnected = false
    setConnectionStatus(brokerIndicator,brokerIsConnected)
}

function onMessageArrived(message) {
    console.log(message.destinationName)
    console.log(message.payloadString)
    data.push(Number(message.payloadString))
    if(message.destinationName == TOPIC_RESPONSE){
        if(message.payloadString == "l0"){
            checkboxLed.checked = true
            nextStateLed = false
            ledIcon.style.color="#ffcc00"
        }else if(message.payloadString == "l1"){
            checkboxLed.checked = false
            nextStateLed = true
            ledIcon.style.color="#fff"
        }
    }else if(message.destinationName == TOPIC_NODE_CONECTION){
        if(message.payloadString == "0x200"){
            if(!nodeIsConnected){
                console.log("NodeMCU Conectado")
                nodeIsConnected = true
                setConnectionStatus(nodeIndicator,nodeIsConnected)
                client.send(TOPIC_REQUEST,"0x09")
            }
        } if(message.payloadString == "0x04"){
            console.log("Sensor analogico recebido")
        }
    }
}

function setConnectionStatus(element,status){
    if(status){
        element.classList.remove("disconnected")
        element.classList.add("connected")
    }else{
        element.classList.remove("connected")
        element.classList.add("disconnected")
    }
    
}

function checkNodeConnection(){
    client.send(TOPIC_NODE_CONECTION,"0x08")
}


