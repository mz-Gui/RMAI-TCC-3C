/*
PROJETO DE TCC - 3C 2023

PROJETO: ROBÔ PARA INSPEÇÂO DE AMBIENTES INÓSPITOS
COMPONENTE: TRANSMISSOR/CONTROLE REMOTO
AUTORES: GRUPO 5 - GUILHERME E MIGUEL

APROVEITE O CÓDIGO ;)
*/

//Inclusão de bibliotecas

#include <RH_ASK.h> //INCLUSÃO DE BIBLIOTECA
#include <SPI.h> //INCLUSÃO DE BIBLIOTECA

//Definição da pinagem usada
#define PIN_RED 6
#define PIN_YELLOW 7
#define PIN_BLUE 8
#define PIN_GREEN 9

RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇ
String str = ""; //VARIÁVEL DO TIPO STRING
int statusLed = 0; //VARIÁVEL DO TIPO INT (CONTROLA O ESTADO ATUAL DO LED)
 
void setup(){
    driver.init(); //INICIALIZA A COMUNICAÇÃO RF DO DRIVER
    Serial.begin(9600);
}
void loop(){
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN]; //LÊ A MENSAGEM RECEBIDA (PALAVRA: led)
    uint8_t buflen = sizeof(buf); //CRIA O COMPRIMENTO DO BUFFER PARA O TAMANHO DE buf
 
    if(driver.recv(buf, &buflen)){ //SE O DRIVER RECEBEU buf(INTEIRO) E buflen (COMPRIMENTO DE DADOS), FAZ
     str = ""; //VARIÁVEL RECEBE VAZIO
     int i; //VARIÁVEL LOCAL DO TIPO INTEIRO
       
     for(int i = 0; i < buflen; i++){ //PARA i IGUAL A 0, ENQUANTO i MENOR QUE buflen, INCREMENTA i
      str += (char)buf[i]; //VARIÁVEL RECEBE OS CARACTERES E FORMA A PALAVRA
      Serial.println(str);
     }  
     Serial.println(str);
      if(str.equals("COMMANDR")) 
        {
        digitalWrite(PIN_YELLOW, HIGH);
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_BLUE, LOW);
        digitalWrite(PIN_GREEN, LOW);
     }
      
      if(str.equals("COMMANDU")){
        digitalWrite(PIN_YELLOW, LOW);
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_BLUE, HIGH);
        digitalWrite(PIN_GREEN, LOW);
     }
      
       if(str.equals("COMMANDL")){
        digitalWrite(PIN_YELLOW, LOW);
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_BLUE, LOW);
        digitalWrite(PIN_GREEN, HIGH);
    
      }
       if(str.equals("COMMANDD")){
        digitalWrite(PIN_YELLOW, LOW);
        digitalWrite(PIN_RED, HIGH);
        digitalWrite(PIN_BLUE, LOW);
        digitalWrite(PIN_GREEN, LOW);
     }

     else {
      digitalWrite(PIN_YELLOW, LOW);
        digitalWrite(PIN_RED, LOW);
        digitalWrite(PIN_BLUE, LOW);
        digitalWrite(PIN_GREEN, LOW);
      }

      }
        }
