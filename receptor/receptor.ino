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
#include <Servo.h>
#include <esp_now.h>
#include <WiFi.h>

//Definições
#define IN1 33
#define IN2 25
#define IN3 26
#define IN4 27

#define SV1 16
#define SV2 17

//Estrutura para o recebimento das mensagens
typedef struct struct_message
{
  String dir;
  String rot;
} struct_message;

//Variavel de comando
struct_message comando;

//Declaração do servo motor
Servo servo1;
Servo servo2;

//Variável de posição dos servos
int horz;
int vert;

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

  horz = 90;
  vert = 90;

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
    horz = horz + 2;
    servo1.write(horz);
    }

  if(rotacao == "direita"){
    horz = horz - 2;
    servo1.write(horz);
    }

    if(rotacao == "frente"){
    vert = vert + 2;
    servo2.write(vert);
    }

  if(rotacao == "tras"){
    vert = vert - 2;
    servo2.write(vert);
    }
}

void setup(){
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servo1.attach(SV1);
  servo2.attach(SV2);

  WiFi.mode(WIFI_STA);

  InitESPNow();

  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  //Relaxe ;)
}
