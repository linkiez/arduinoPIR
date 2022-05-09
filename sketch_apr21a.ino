#include <PubSubClient.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>

#include "WiFiEsp.h" //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
 
char ssid[] = "LiNkIeZ"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO
char pass[] = "99241665";//VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO

const int pinoRELE = 10;
const int pinoPIR = 4;

WiFiEspClient wifiClient;
PubSubClient client(wifiClient);

 
int status = WL_IDLE_STATUS; //STATUS TEMPORÁRIO ATRIBUÍDO QUANDO O WIFI É INICIALIZADO E PERMANECE ATIVO
//ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
//(RESULTANDO EM WL_CONNECTED)
 

RingBuffer buf(8); //BUFFER PARA AUMENTAR A VELOCIDADE E REDUZIR A ALOCAÇÃO DE MEMÓRIA
 
void setup(){
  pinMode(pinoRELE, OUTPUT);
  pinMode(pinoPIR, INPUT);
  
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
  
  client.setServer("192.168.0.2", 1883);
  client.setKeepAlive(10);
}

long lastReconnectAttempt = 0;

boolean reconnect() {
  if (client.connect("arduinoClient")) {
    // Once connected, publish an announcement...
    //client.publish("teste","hello world");
    // ... and resubscribe
    //client.subscribe("teste");
  }
  return client.connected();
}

 
void loop(){
  
   if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    int valor = digitalRead(pinoPIR);
    if (valor == HIGH) {
    Serial.println("DETECTED");
    digitalWrite(pinoRELE, HIGH);

    delay(3000);
    
    client.publish("teste", "MOVIMENTO DETECTADO");
    digitalWrite(pinoRELE, LOW);
  }
    client.loop();
  }
  
  int valor = digitalRead(pinoPIR);
  
}
 
