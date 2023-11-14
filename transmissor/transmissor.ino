/*
PROJETO DE TCC - 3C 2023

PROJETO: ROBÔ PARA MONITORAMENTO DE AMBIENTES INÓSPITOS
COMPONENTE: TRANSMISSOR/CONTROLE REMOTO
AUTORES: GRUPO 5 - GUILHERME E MIGUEL

PROPÓSITO: PROGRAMAÇÃO DO CONTROLE REMOTO DO PROJETO DE TCC - RMAI

SAIBA MAIS EM: 

APROVEITE O CÓDIGO ;)
*/

//Inclusão de bibliotecas
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

//Definições
#define xPin1 35
#define yPin1 34
#define xPin2 33
#define yPin2 32

//Declaração de variáveis
int eixo_X1;
int eixo_Y1;
int eixo_X2;
int eixo_Y2;

esp_now_peer_info_t peerInfo;

//Endereço MAC do receptor
uint8_t broadcastAddress[] = {0xA0, 0xB7, 0x65, 0x4F, 0x3A, 0x34};

//Estrutura para o envio das mensagens
typedef struct struct_message
{
  String dir;
  String rot;
} struct_message;

//Variavel de comando
struct_message comando;


//Inicialização do protocolo de comunicação ESP-NOW
void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("Iniciado com sucesso");
  }
  else {
    Serial.println("Erro de inicialização");
    ESP.restart();
  }
}

//Função de callback para o envio de dados 
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

//Setup
void setup(){
  Serial.begin(115200);

  pinMode(xPin1, INPUT);
  pinMode(yPin1, INPUT);
  pinMode(xPin2, INPUT);
  pinMode(yPin2, INPUT);

  WiFi.mode(WIFI_STA);

  InitESPNow();

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
       
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

}

//loop
void loop(){
  eixo_X1 = analogRead(xPin1);
  eixo_Y1 = analogRead(yPin1);
  eixo_X2 = analogRead(xPin2);
  eixo_Y2 = analogRead(yPin2);

  comando.dir = "parado";
  comando.rot = "parado";

  if(eixo_X1<1188){
    comando.dir = "tras";
  }

  if(eixo_X1>2212){
    comando.dir = "frente";
  }

  if(eixo_Y1<1188){
    comando.dir = "esquerda";
  }
  
  if(eixo_Y1>2212){
    comando.dir = "direita";
}

//Rotina de rotação da Camera

if(eixo_X2<1188){
    comando.rot = "tras";
  }

  if(eixo_X2>2212){
    comando.rot = "frente";
  }

  if(eixo_Y2<1188){
    comando.rot = "esquerda";
  }
  
  if(eixo_Y2>2212){
    comando.rot = "direita";
}

    
  //Serial.println(eixo_X1);
  //Serial.println(eixo_Y1);
  Serial.println(comando.dir);
  Serial.print(comando.rot);

  esp_now_send(broadcastAddress, (uint8_t *) &comando, sizeof(comando));
}
