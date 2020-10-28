#include "ACS712.h"
 
// Estou usando ACS de 30A. Mude para o modelo que está usando. Valores possíveis: 5,20 e 30
// Sensor ligado na porta analópgica A0
ACS712 sensor(ACS712_30A, A0);
const int analogOutPin1 = A1;
const int analogOutPin2 = 9;
float lastI = 0;
float lastLastI = 0;
 
void setup() {
  // É necessário calibrar o sensor antes de usar a primeira vez com o método abaixo
  Serial.begin(9600);
  Serial.println("Aguarde. Calibrando..."); 
  sensor.calibrate();
  Serial.println("Fim da calibração");
}
 
void loop() {
  // A frequência da corrente alternada no Brasil é 60 Hz. Mude caso necessário
  // A voltagem, no meu caso é 127
  delay(5000);
  float V = 127;
  float I = sensor.getCurrentAC(60);
  float P = V * I;
 
  Serial.println(String("Corrente = ") + I + " A");
  Serial.println(String("Potência  = ") + P + " Watts");

  if (lastI > 0.2f && lastLastI > 0.2f && I < 0.2f) {
    Serial.println("Desarmando");
    analogWrite(analogOutPin1, 1023);
    analogWrite(analogOutPin2, 1023);
  } else {
    analogWrite(analogOutPin1, 0);
    analogWrite(analogOutPin2, 0);
  }
  lastLastI = lastI;
  lastI = I;
}
