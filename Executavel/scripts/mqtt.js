const TOPIC_RESPONSE = "leds/response"
const TOPIC_NODE_CONECTION = "leds/status"
const TOPIC_REQUEST = "leds/request"
const TOPIC_ANALOG_SENSOR = "leds/sensor-analogico"
const TOPIC_DIGITAL_SENSOR = "leds/sensor-digital"

const nodeIndicator = document.getElementById("node-indicator")
const brokerIndicator = document.getElementById("broker-indicator")
 //Definindo variaveis que informam se o broker
let brokerIsConnected = false
let nodeIsConnected = false
let nextStateLed = false

var data = []; //definindo lista para inserção de dados

let pahoConfig = { //Configurações para acessar o Broker
    hostname: "10.0.0.101",  //The hostname is the url, under which your FROST-Server resides.
    port: 9001,
              //The port number is the WebSocket-Port,
                            // not (!) the MQTT-Port. This is a Paho characteristic.
    clientId: "APP-TP04/G01"    //Should be unique for every of your client connections.
}

let client = new Paho.MQTT.Client(pahoConfig.hostname, Number(pahoConfig.port), pahoConfig.clientId);
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

client.connect({ //iniciando a conexão com o usuario e senha
    userName: "aluno",
    password: "@luno*123", 
    onSuccess: onConnect,
    onFailure:onFailureConnect,
    reconnect:true,
})

function onFailureConnect(){ //caso a conexão falhe retorna essa informa essa mensagem
    console.log("Falha ao tentar se conectar")
}

function onConnect() { //conexão bem sucedida entra nessa função
    // Once a connection has been made, make a subscription and send a message.
    console.log("Conexão estabelecida")
    brokerIsConnected = true
    client.subscribe(TOPIC_RESPONSE)
    client.subscribe(TOPIC_NODE_CONECTION)
    setConnectionStatus(brokerIndicator,brokerIsConnected)
    client.send(TOPIC_REQUEST,"0x08")
    client.send(TOPIC_ANALOG_SENSOR, "0x04")
}

function onConnectionLost(responseObject) { //função para caso de conexão perdida
    console.log(responseObject)
    if (responseObject.errorCode !== 0) {
        console.log("onConnectionLost:" + responseObject.errorMessage);
    }
    brokerIsConnected = false
    setConnectionStatus(brokerIndicator,brokerIsConnected)
}

function onMessageArrived(message) { //função para definir as mensagens de um subscriber
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
    }else if(message.destinationName == TOPIC_NODE_CONECTION){ //condicao para conexão da node
        if(message.payloadString == "0x200"){
            if(!nodeIsConnected){
                console.log("NodeMCU Conectado")
                nodeIsConnected = true
                setConnectionStatus(nodeIndicator,nodeIsConnected)
                client.send(TOPIC_REQUEST,"0x09")
            }
        } if(message.payloadString == "0x04"){ //condicao para conexão com o sensor analogico bem sucedido
            console.log("Sensor analogico recebido")
        }
    }
}

function setConnectionStatus(element,status){ //função para enviar ondição de status
    if(status){
        element.classList.remove("disconnected")
        element.classList.add("connected")
    }else{
        element.classList.remove("connected")
        element.classList.add("disconnected")
    }
    
}

function checkNodeConnection(){ //função para checar condição da Node
    client.send(TOPIC_NODE_CONECTION,"0x08")
}


