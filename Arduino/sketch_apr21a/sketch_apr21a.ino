#include <PubSubClient.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>

#include "WiFiEsp.h" //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
 
char ssid[] = "LiNkIeZ"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO
char pass[] = "99241665";//VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO

const int pinoRELE = 10; //DEFINE VARIAVEL PARA PINO DO RELE NO ARDUINO
const int pinoPIR = 4; //DEFINE VARIAVEL PARA PINO DO PIR NO ARDUINO

WiFiEspClient wifiClient; //INSTANCIA BIBLIOTECA DE WIFI
PubSubClient client(wifiClient); //INSTACIA BIBLIOTECA MQTT E CONFIGURA COM WIFI

 
int status = WL_IDLE_STATUS; //STATUS TEMPORÁRIO ATRIBUÍDO QUANDO O WIFI É INICIALIZADO E PERMANECE ATIVO
//ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
//(RESULTANDO EM WL_CONNECTED)
 

RingBuffer buf(8); //BUFFER PARA AUMENTAR A VELOCIDADE E REDUZIR A ALOCAÇÃO DE MEMÓRIA
 
void setup(){
  pinMode(pinoRELE, OUTPUT); //DEFINE PINO DE RELE 10 COMO DE SAIDA
  pinMode(pinoPIR, INPUT); //DEFINE PINO DO PIR 4 COMO DE ENTREDA
  
  Serial.begin(9600); //INICIALIZA A SERIAL
  WiFi.init(&Serial); //INICIALIZA A COMUNICAÇÃO SERIAL COM O SHIELD WIFI ESP8266
  WiFi.config(IPAddress(192,168,0,15)); //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR
 
  //INÍCIO - VERIFICA SE O SHIELD ESTÁ ACOPLADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER
  if(WiFi.status() == WL_NO_SHIELD){
    while (true);
  }
  while(status != WL_CONNECTED){
    status = WiFi.begin(ssid, pass);
  }
  //FIM - VERIFICA SE O SHIELD ESTÁ ACOPLADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER
  
  client.setServer("192.168.0.2", 1883); //CONFIGURA ENDEREÇO DO MQTT BROKER E PORTA
  client.setKeepAlive(10); //CONFIGURA QUANTO TEMPO A CONEXÃO DEVE FICAR ATIVA
}

long lastReconnectAttempt = 0;

boolean reconnect() {
  if (client.connect("arduinoClient")) { // CONECTA CLIENTE AO MQTT BROKER
    // Once connected, publish an announcement...
    //client.publish("teste","hello world");
    // ... and resubscribe
    //client.subscribe("teste");
  }
  return client.connected(); // RETORNA OBJETO CONECTADO
}

 
void loop(){
  
   if (!client.connected()) { // SE CLIENTE NÃO ESTA CONECTADO ENTÃO
    long now = millis(); // VARIAVEL RECEBE TEMPO DO ARDUINO LIGADO EM MILISSEGUNDOS
    if (now - lastReconnectAttempt > 5000) { // SE ULTIMA TENTATIVA DE CONEXÃO FOI A MAIS DE 5 SEGUNDOS ENTÃO
      lastReconnectAttempt = now; // GUARDA NA VARIAVEL O TEMPO DA ULTIMA TENTATIVA DE CONEXÃO
      
      if (reconnect()) { // TENTA SE RECONECTAR ENTÃO
        lastReconnectAttempt = 0; // GUARDA NA VARIAVEL O TEMPO DA ULTIMA TENTATIVA DE CONEXÃO IGUAL A ZERO
      }
    }
  } else { // SENÃO (LINHA 61)
    // Client connected
    int valor = digitalRead(pinoPIR); // FAZ A LEITURA DE ESTADO DO PINO PIR
    if (valor == HIGH) { // SE O PIR ESTIVER ACIONADO
    Serial.println("DETECTED"); // PRINTA NO CONSOLE
    digitalWrite(pinoRELE, HIGH); // LIGA O LED

    delay(3000); // ESPERA 3 SEGUNDOS
    
    client.publish("teste", "MOVIMENTO DETECTADO"); // PUBLICA MENSAGEM NO MQTT BROKER
    digitalWrite(pinoRELE, LOW); // DESLIGA O LED
  }
    client.loop(); // MANTEM CONEXÃO ATIVA
  }
  
  int valor = digitalRead(pinoPIR);
  
}
 
