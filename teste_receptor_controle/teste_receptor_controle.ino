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
#define OUT1 6
#define OUT2 7
#define OUT3 8
#define OUT4 9

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
        digitalWrite(OUT1, HIGH);
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, HIGH);
     }
      
      if(str.equals("COMMANDU")){
        digitalWrite(OUT1, HIGH);
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, HIGH);
        digitalWrite(OUT4, LOW);
     }
      
       if(str.equals("COMMANDL")){
        digitalWrite(OUT1, LOW);
        digitalWrite(OUT2, HIGH);
        digitalWrite(OUT3, HIGH);
        digitalWrite(OUT4, LOW);
    
      }
       if(str.equals("COMMANDD")){
        digitalWrite(OUT1, LOW);
        digitalWrite(OUT2, HIGH);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, HIGH);
     }

     else {
      digitalWrite(OUT1, LOW);
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, LOW);
      }

      }
        }
