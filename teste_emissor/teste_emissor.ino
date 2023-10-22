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
#define VRX_PIN  A0 
#define VRY_PIN  A1 

//Valores e variáveis
#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08
int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int command = COMMAND_NO;


RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO
 
 
void setup(){
    driver.init(); 
    Serial.begin(9600);
}

void loop(){
    xValue = analogRead(VRX_PIN);
    yValue = analogRead(VRY_PIN);
    const char *msg = ""; 
    command = COMMAND_NO;
    
    if (xValue < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
    else if (xValue > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;


    if (yValue < UP_THRESHOLD)
    command = command | COMMAND_UP;
    else if (yValue > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;
    
    if (command & COMMAND_LEFT){
      msg = "COMMANDL"; //VARIÁVEL RECEBE O VALOR (led)
    }
      
    if (command & COMMAND_RIGHT) {
      msg = "COMMANDR"; //VARIÁVEL RECEBE O VALOR (led)
    }

    if (command & COMMAND_UP) {
      msg = "COMMANDU"; //VARIÁVEL RECEBE O VALOR (led)
    }
      
    if (command & COMMAND_DOWN) {
      msg = "COMMANDD"; //VARIÁVEL RECEBE O VALOR (led)
    }       
 
    Serial.println(msg);
    Serial.println(command);
    driver.send((uint8_t *)msg, strlen(msg)); //ENVIA AS INFORMAÇÕES PARA O RECEPTOR (PALAVRA: led)
    driver.waitPacketSent(); //AGUARDA O ENVIO DAS INFORMAÇÕES
    }
