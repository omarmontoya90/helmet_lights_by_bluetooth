//***************************************************************
//**El codigo permite la comunicación entre el modulo HC05 y un**
//**dispositivo bluetooth (celular). Permite encender o apagar **
//**un led, al enviar el comando "L".                          **
//**El nombre del modulo HC05 es "CASCO OMAR"                  **
//**La contraseña para permitir la comunicacion es "1014"      **
//***************************************************************

#include <SoftwareSerial.h>

#define TX 7
#define RX 8
#define KEY 9
#define RST 10
#define LED 13
#define BTN 11 //11

SoftwareSerial BTserial(TX,RX);  //SE CONECTA TAL CUAL AL MODULO HC 05
//byte pinEstado=0;
int conteo=0;

void setup() {
  pinMode(BTN,INPUT);
  //pinMode(BTN,INPUT);
  //attachInterrupt(BTN, cambio, FALLING); //Configuración de la interrupcion en el pin12
  pinMode(RST,OUTPUT);   //Pin para encender o apagar el HC-05. Funciona a 3.3V y 5V
  pinMode(KEY,OUTPUT);
  pinMode(LED,OUTPUT);//salida para el led
  
  digitalWrite(LED,HIGH); //dipositivo cambia estando en bajo 
  //digitalWrite(RST,LOW); //Apaga el modulo hc-05
  digitalWrite(KEY,LOW); //Habilita Bluetooth
  digitalWrite(RST,HIGH); //Enciende Modulo HC05
  
  Serial.begin(9600);  
  BTserial.begin(9600);// a esta velocidad se trabaja comandos AT
  Serial.println("Listo");
  
}

void loop() {
  // Esperamos ha recibir datos.
  if (BTserial.available()){
    char infoAndroid = BTserial.read();
    BTserial.flush();
    Serial.println(infoAndroid);
    
    // En caso de que el caracter recibido sea "L" cambiamos
    // El estado del LED
    if (infoAndroid == 'L'){
      Serial.println("Cambio estado de LED");
      BTserial.write("Estado: ");
      cambio(); 
    }
  }
  
  if(digitalRead(BTN)==HIGH){
    Serial.println("hola");
    BTserial.write("Estado: ");
    cambio();
  }
  
}

void cambio(){

  switch (conteo){
    case 0:
      BTserial.write("encendido");
      oprimir(LED);
      conteo++;
    break;
    case 1:
      BTserial.write("lento");
      oprimir(LED);
      conteo++;
    break;
    case 2:
      BTserial.write("rapido");    
      oprimir(LED);
      conteo++;
    break;
    case 3:
      BTserial.write("apagado");
      oprimir(LED);
      conteo=0;    
    break;
    default:
      conteo=0;
    break;
  }
  
  
}

void oprimir(int pinNum)
{
  digitalWrite(pinNum,HIGH);
  delay(500);
  digitalWrite(pinNum, LOW);

}
/*
void estadoLed(int pinNum){
    digitalWrite(pinNum, pinEstado);
    pinEstado=!pinEstado;
}*/
