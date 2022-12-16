<h1 align="center">PROBLEMA 3 TEC 499 - IoT: A Internet das Coisas</h1>

<p align="center">O problema proposto consiste em melhorias do problema proposto anteriormente (https://github.com/tassiocarvalho/Problema2InterfacesDeEntrada-Saida) sobre um protótipo de sistema de sensoriamento genérico. Desta forma, para acompanhar a modernização das tecnologias os requisitos mudaram para atender a nova demanda, portanto, o desenvolvimento de um sistema com sensores sem fio é o objetivo principal deste projeto.
	
O Single Board Computer (SBC) continuará exercendo o seu papel de comandar o sistema acompanhado dos requisitos do problema anterior e centralizar as informações para ser possível acessar os dados através da internet. Ademais, uma interface homem-máquina (IHM) para apresentações, em tempo real e o histórico das dez últimas medições de cada sensor e das leituras dos sensores tanto de forma remota quanto local fez-se necessário.
</p>

Sumário
=================
<!--ts-->
   * [Status do projeto](#status-do-projeto)
   * [Features](#features)
   * [Descrição em alto nível do sistema](#descricao-em-alto-nivel-do-sistema)
   * [Metodologias e técnicas aplicadas para o projeto](#metodologias-tecnicas-aplicadas-para-o-projeto)
   * [Desenvolvimento da solução do problema](#desenvolvimento-da-solucao-do-problema)
   * [Tecnologias utilizadas](#tecnologias-utilizadas)
   * [Pré-requisitos e instruções de instalação](#pre-requisitos-e-instrucoes-de-instalacao)
      * [Pré-requisitos](#pre-requisitos)
      * [Instruções de instalação](#instrucoes-de-instalacao)
   * [Instruções de uso do sistema](#instrucoes-de-uso-do-sistema)
   * [Descrição e análise dos testes e simulações](#descricao-e-analise-dos-testes-e-simulacoes)
   * [Autores](#autores)
   * [Referências](#referencias)
<!--te-->

<h1 id="status-do-projeto">Status do projeto</h1>
<h4 align="center"> 
	🚧 Em construção...  🚧
</h4>

<h1 id="features">Features</h1>

- [ ] Suporta até 8 sensores
- [ ] Status dos sensores
- [ ] Solicitação e resposta de comandos
- [x] Comunicação utilizando o protocolo MQTT
- [x] Gráfico com 10 medições
- [ ] Ajuste de tempo na interface
- [ ] Status da conexão
- [ ] IHM no SBC
- [ ] Histórico de 10 medições
- [ ] Interface para ajuste de tempo
- [x] Dados via MQTT com a ESP

<h1 id="descricao-em-alto-nivel-do-sistema">Descrição em alto nível do sistema</h1>

<p>A solução apresentada neste repositório consiste no envio de informações via protocolo MQTT do NodeMCU para o broker e da Raspberry para o broker. As informações são enviadas para a Raspberry e para a aplicação feita, sendo possível, assim, exibir as informações do histórico tanto no LCD quanto no gráfico temporal disponível no executável.

O principal fluxo de informações são os protocolos criados para efetuar a conexão MQTT sendo feitos os comandos de publish e subscribe para publicar e receber os dados fornecidos.

O sistema continua sendo comandado pelo Single Board Computer (SBC), e todos os requisitos anteriormente solicitados para o sistema com a UART atendidos. O projeto em questão não conseguiu atender todos os requisitos listados no problema, sendo possível somente o suporte até 3 sensores, a comunicação MQTT, a interface remota com o gráfico exibindo as medições e os dados via MQTT com a ESP.

Segue abaixo o diagrama do sistema proposto e entendido pela equipe:
</p>

![image](https://user-images.githubusercontent.com/71518539/207993462-f1f2579c-c097-4b0a-ad7b-9e75eb10ee92.png)



<h1 id="metodologias-tecnicas-aplicadas-para-o-projeto">Metodologias e técnicas aplicadas para o projeto</h1>

<p>Com o intuito de desenvolver um sistema com sensores sem fio a necessidade de encaminhar os dados através de um broker localizado no laboratório LEDS da Universidade Estadual de Feira de Santana. Para utilizar o Broker o protocolo MQTT fez-se necessário, onde essa comunicação possui um cliente responsável por fazer uma publicação (Publish) e transmitirá uma mensagem com um tópico de destino e o conteúdo da mensagem (também chamado de Payload). A mensagem em questão é transmitida para o Broker que é responsável por gerir e encaminhar um Subscriber, oriundo do tópico inscrito anteriormente. 

Essa comunicação foi feita tanto para permitir a comunicação entre a Raspberry, a NodeMCU e o executável através desse processo fornecido pelo protocolo MQTT através do Broker.

Na Raspberry Pi também foi necessário fazer o uso de biblioteca ____ para permitir que o código funcionasse também na Orange Pi.
</p>

<h1 id="desenvolvimento-da-solucao-do-problema">Desenvolvimento da solução do problema</h1>

<p>
O desenvolvimento do projeto se iniciou com pesquisas relacionadas ao protocolo MQTT e suas funcionalidades, como acessar a um Broker privado e como os tópicos funcionam. 

Houve também a necessidade de uma implementação de um código direcionada tanto a uma Orange Pi quanto uma Raspberry Pi.

Posteriormente fizemos s modificação do código mostrado no problema dois substituindo a conexão UART com a comunicação via protocolo MQTT no código da NodeMCU e Rasp, definindo assim os tópicos e fazendo login no Broker para fim de testes.

Por fim, o desenvolvimento do executável, utilizando uma biblioteca chama Paho-MQTT, com o objetivo de permitir a conexão também do executável com o Broker e assim com o protocolo MQTT.

Devemos salientar que o projeto final não alcançou as expectativas por não cumprir os requisitos solicitados podendo ser complementado com as funcionalidades faltantes e melhorado as que constam neste repositório.
</p>

<h1 id="tecnologias-utilizadas">Tecnologias utilizadas</h1>

<p>Foi necessário a utilização do Arduino IDE para executar os códigos na NodeMCU (ESP8266).

Para fazer a interface remota, utilizando as linguagens: HTML, CSS e JavaScript foi necessário dispor da IDE Visual Studio Code.
	
Ademais, a Raspberry Pi Zero usamos também a IDE mencionada anteriormente, desta forma, conseguimos também programar as funcionalidades dos botões, chaves e o potenciômetro.</p>


As seguintes ferramentas foram usadas na construção do projeto:

- [Assembly](https://www.tutorialspoint.com/assembly_programming/assembly_basic_syntax.htm)
- [JavaScript](https://www.javascript.com)
- [C](https://devdocs.io/c/)
- [HTML](https://html.com)
- [CSS](https://developer.mozilla.org/pt-BR/docs/Web/CSS)

<h1 id="pre-requisitos-e-instrucoes-de-instalacao">Pré-requisitos e instruções de instalação</h1>

<h2 id="pre-requisitos">Pré-requisitos</h2>

<p>

Antes de começar recomendamos que caso não possua na sua máquina os recursos listados a seguir faça a instalação:

* Git
* Arduiíno

Além disto é bom ter um editor para visualizar e editar o código como o Visual Studio Code.
</p>

<h2 id="instrucoes-de-instalacao">Instruções de instalação</h2>

<h3>Raspberry Pi</h3>

<p>Para executar é necessário clonar o projeto na sua máquina usando o comando a seguir:</p>

```
https://github.com/tassiocarvalho/Problema3IoT-InternetDasCoisas.git
```

<p>Transfira os seguintes arquivos baixados para o Raspberry Pi:</p>


```
$ main.c
$ makefile
```


<h3>ESP8266</h3>

<p>Utilizando o software Arduino para utilizar compilar o código destinado a NodeMCU no arquivo abaixo:</p>


```
$ EspMain.ino
```


<p>E em seguida compilar o código na plataforma e fazer o upload.</p>

<h3>Executável</h3>

<p>Abrindo as pastas de nome:</p>


```
$ .vdcode
$ scripts
$ style
```


<p>E o arquivo index.html na IDE de sua preferência (recomendamos o Visual Studio Code) e abra o link abaixo em seu navegador (recomendamos o Chrome):</p>

[index](http://127.0.0.1:5501/index.html)

<p>Por fim, execute os seguintes comandos: </p>


```
$ make
$ sudo /.main
```


<h1 id="instrucoes-de-uso-do-sistema">Instruções de uso do sistema</h1>


<h1 id="descricao-e-analise-dos-testes-e-simulacoes">Descrição e análise dos testes e simulações</h1>


<h1 id="autores">Autores</h1>

<a href="https://github.com/AlanaSampaio">Alana Sampaio</a>  
<a href="https://github.com/tassiocarvalho">Tassio Carvalho</a>

<h1 id="referencias">Referências</h1>

[Datasheet - ESP8266](https://www.alldatasheet.com/view.jsp?Searchword=ESP8266&sField=4&gclid=Cj0KCQiAmaibBhCAARIsAKUlaKRSP5JzpmlF9JPnfCkdjKYD79a6Dcb_OL1NOG1STKnfcAP_e4Yg6s4aAjbzEALw_wcB)

[MQTT](https://mqtt.org)

[Paho - MQTT](https://www.eclipse.org/paho/files/jsdoc/index.html)

[Orange Pi](http://www.orangepi.org/html/hardWare/computerAndMicrocontrollers/details/Orange-Pi-PC.html)
