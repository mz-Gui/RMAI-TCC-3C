 /*
PROJETO DE TCC - 3C 2023

PROJETO: ROBÔ PARA MONITORAMENTO DE AMBIENTES INÓSPITOS
COMPONENTE: TRANSMISSOR/CONTROLE REMOTO
AUTORES: GRUPO 5 - GUILHERME

PROPÓSITO: PROGRAMAÇÃO DO RECEPTOR DO PROJETO DE TCC - RMAI

SAIBA MAIS EM: 

APROVEITE O CÓDIGO ;)
*/

//Inclusão de bibliotecas
#include <Stepper.h>
#include <esp_now.h>
#include <WiFi.h>

//Definições
#define IN1 33
#define IN2 25
#define IN3 26
#define IN4 27

#define SV1 19
#define SV2 18
#define SV3 5
#define SV4 17

//Estrutura para o recebimento das mensagens
typedef struct struct_message
{
  String dir;
  String rot;
} struct_message;

//Variavel de comando
struct_message comando;

//Declaração do servo motor
Stepper myStepper(1024, SV1, SV3, SV2, SV4);

//Inicializar o protocolo de comunicação espNow
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

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len){
  memcpy(&comando, incomingData, sizeof(comando));
  
  Serial.println(comando.dir);
  String direcao = comando.dir;

  Serial.print(comando.rot);
  String rotacao = comando.rot;

//rotina de controle

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  if(direcao == "direita") {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
      
  if(direcao == "frente"){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
      
  if(direcao == "esquerda"){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);  
  }

  if(direcao == "tras"){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

//Rotina de controle da rotação
  if(rotacao == "esquerda"){
    myStepper.step(4);
    }

  if(rotacao == "direita"){
    myStepper.step(-4);
    }
}

void setup(){
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  WiFi.mode(WIFI_STA);

  InitESPNow();

  myStepper.setSpeed(24);

  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  //Relaxe ;)
}
