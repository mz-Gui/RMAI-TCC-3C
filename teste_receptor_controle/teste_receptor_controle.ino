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
#define INT_1 4
#define INT_2 3
#define INT_3 2
#define INT_4 1
//Definição da pinagem usada passo
#define IN_1 5
#define IN_2 6
#define IN_3 7
#define IN_4 8
#define IN_5 13
#define IN_6 12
#define IN_7 10
#define IN_8 9

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
      if(str.equals("R")) 
        {
        digitalWrite(INT_1, HIGH);
        digitalWrite(INT_2, LOW);
        digitalWrite(INT_3, LOW);
        digitalWrite(INT_4, HIGH);
     }
      
      if(str.equals("U")){
        digitalWrite(INT_1, HIGH);
        digitalWrite(INT_2, LOW);
        digitalWrite(INT_3, HIGH);
        digitalWrite(INT_4, LOW);
     }
      
       if(str.equals("L")){
        digitalWrite(INT_1, LOW);
        digitalWrite(INT_2, HIGH);
        digitalWrite(INT_3, HIGH);
        digitalWrite(INT_4, LOW);
    
      }
       if(str.equals("D")){
        digitalWrite(INT_1, LOW);
        digitalWrite(INT_2, HIGH);
        digitalWrite(INT_3, LOW);
        digitalWrite(INT_4, HIGH);
    
     }

     else {
      digitalWrite(INT_1, LOW);
      digitalWrite(INT_2, LOW);
      digitalWrite(INT_3, LOW);
      digitalWrite(INT_4, LOW);
      }
      while(str.equals("E")) 
        {
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(50);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(50);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        delay(50);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
     }
      
      while(str.equals("H")) 
        {
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
        delay(50);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        delay(50);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(50);
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
     }
      
       while(str.equals("C")) 
        {
        digitalWrite(IN_5, HIGH);
        digitalWrite(IN_6, LOW);
        digitalWrite(IN_7, LOW);
        digitalWrite(IN_8, LOW);
        delay(50);
        digitalWrite(IN_5, LOW);
        digitalWrite(IN_6, HIGH);
        digitalWrite(IN_7, LOW);
        digitalWrite(IN_8, LOW);
        delay(50);
        digitalWrite(IN_5, LOW);
        digitalWrite(IN_6, LOW);
        digitalWrite(IN_7, HIGH);
        digitalWrite(IN_8, LOW);
        delay(50);
        digitalWrite(IN_5, LOW);
        digitalWrite(IN_6, LOW);
        digitalWrite(IN_7, LOW);
        digitalWrite(IN_8, HIGH);
     }
       while(str.equals("B")) 
        {
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
        delay(50);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
        delay(50);
        digitalWrite(IN_1, LOW);
        digitalWrite(IN_2, HIGH);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
        delay(50);
        digitalWrite(IN_1, HIGH);
        digitalWrite(IN_2, LOW);
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, LOW);
     }

      }
        }