#include <SoftwareSerial.h>

/*  Essa é a versão nível 1 do projeto RAS Balloon,
* um projeto com o propósito de introduzir o manejo de microcontroladores
* através da plataforma arduíno.
* Este código é livre, e pode ser alterado e distribuído conforme a licensa xxx
*/


/*
******************
* Mapeando Pinos *  
******************
*/

// motores
#define motorA1 2
#define motorA2 3
#define motorB1 4
#define motorB2 2

// HC-05
#define btTx 2
#define btRx 4
/*
****************
* MOTOR Config *  
****************
*/


#define V 120

void setup_motor() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA1, OUTPUT);
}

void run(int va, int vb) {
  if (va > 0) {
    analogWrite(motorA1, va);
    analogWrite(motorA2, 0);
  } else {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, va);
  }

  if (vb > 0) {
    analogWrite(motorB1, vb);
    analogWrite(motorB2, 0);
  } else {
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vb);
  }
}


SoftwareSerial btSerial(btRx, btTx);

void setup() {
  //Iniciando portas seriais
  Serial.begin(115200);
  btSerial.begin(9600);

  // put your setup code here, to run once:
  setup_motor();
}

void loop() {
  // put your main code here, to run repeatedly:
  static char motor_state = '0';

  if (btSerial.available()) {
    motor_state = btSerial.read();
    switch (motor_state) {
      case 'F':
        run(V, V);
        break;
      case 'B':
        run(-V, -V);
        break;
      case 'L':
        run(-V, V);
        break;
      case 'R':
        run(V, -V);
        break;
      default:
        run(0, 0);
    }
  }
}
