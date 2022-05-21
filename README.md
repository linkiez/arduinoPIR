# Sensor inteligente de detecção e registro de movimentos
O projeto desse repositório foi desenvolvido pelos alunos Fabio Moreno e Rosilene G Ghensev Peres para a disciplina de Objetos Inteligentes Conectados. 
Professor Wallace Rodrigues de Santana - Universidade Presbiteriana Mackenzie (UPM)

##🚀 Introdução

O projeto consiste na utilização de sensor infravermelho PIR, um Arduíno e uma placa shield para controlar um LED, que acenderá automaticamente quando o sensor detectar uma presença e movimento. Assim como também irá registrar esses movimentos em um banco de dados. 

##🛠 Pré-requisitos: Hardwares e Softwares utilizados
Para a montagem do circuito do projeto, foram utilizados os seguintes componentes de hardware:
- Arduino Uno;
- Módulo PIR;
- Placa de ensaio;
- Lâmpada LED;
- Placa de Wifi.

**As ferramentas que utilizamos:**
- Fios para a conexão.

**Os softwares utilizados foram:**
- Arduino IDE;
- Plataforma TinkerCad;

**O protocolo de rede utilizado foi:**
- MQTT
Executado através do agente de mensagens:
- Eclipse Mosquitto

##💡 Links úteis:

Tutoriais úteis para o projeto

* [Tutorial para utilizar o Mosquitto](https://kb.elipse.com.br/aplicacao-exemplo-driver-mqtt-em-comunicacao-com-broker-mosquitto-mqtt/)
* [Tutorial do Arduino IDE](https://www.robocore.net/tutoriais/instalando-arduino-ide)
* [Tutorial para Adicionar Bibliotecas à IDE do Arduino](https://www.robocore.net/tutoriais/adicionando-bibliotecas-na-ide-arduino)
* [Tutorial para instalação do Node.Js](https://nodejs.org/pt-br/download/package-manager/)

##⚙ Inicialização do projeto

1 - Este projeto utiliza o Node.js para desenvolvimento e teste. Confirme se o mesmo está instalado, com o seguinte comando:

```
node --version
```

Caso não tenha instalado, prossiga com a instalação utilizando o link do tutorial disponível na seção "Links úteis"

2 - Use npm para instalar a biblioteca cliente MQTT.js 

```
# create a new project
npm init -y
```

```
# Install dependencies
npm install mqtt --save
```

O arquivo **index.js** foi criado no diretório como arquivo de entrada do projeto. Nele implementamos a lógica completa do teste de conexão MQTT.
