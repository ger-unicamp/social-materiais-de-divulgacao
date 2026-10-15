#include <Wire.h>
#include "Adafruit_TCS34725.h"

const int IN1 = 27; 
const int IN2 = 26;
const int IN3 = 25;
const int IN4 = 33;

Adafruit_TCS34725 tcsEsq = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcsDir = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);

const int limiarCalibracao = 2000; 

// Velocidade base (0 a 255). Inicia em 100% (Azul/Padrão)
int velocidadePWM = 255; 

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Wire.begin(21, 22);
  Wire1.begin(14, 12);

  tcsEsq.begin(0x29, &Wire);
  tcsDir.begin(0x29, &Wire1);
}

void moverFrente(int vel) {
  analogWrite(IN1, vel);
  digitalWrite(IN2, LOW);
  analogWrite(IN3, vel);
  digitalWrite(IN4, LOW);
}

void virarEsquerda(int vel) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(IN3, vel);
  digitalWrite(IN4, LOW);
}

void virarDireita(int vel) {
  analogWrite(IN1, vel);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Verifica a cor com base no RGB e ajusta o PWM
void atualizarVelocidade(uint16_t r, uint16_t g, uint16_t b) {
  if (r == 0 && g == 0 && b == 0) return;

  // Vermelho: R dominante
  if (r > g * 1.5 && r > b * 1.5) {
    velocidadePWM = 76; // ~30% de 255
  } 
  // Azul: B dominante
  else if (b > r * 1.2 && b > g * 1.2) {
    velocidadePWM = 255; // 100% de 255
  } 
  // Amarelo: R e G altos, B baixo
  else if (r > b * 1.5 && g > b * 1.5) {
    velocidadePWM = 153; // ~60% de 255
  }
}

void loop() {
  uint16_t r1, g1, b1, c1;
  uint16_t r2, g2, b2, c2;

  tcsEsq.getRawData(&r1, &g1, &b1, &c1);
  tcsDir.getRawData(&r2, &g2, &b2, &c2);

  // Usa a média dos dois sensores para detectar a cor da pista/marcador
  atualizarVelocidade((r1 + r2) / 2, (g1 + g2) / 2, (b1 + b2) / 2);

  bool linhaEsq = (c1 < limiarCalibracao);
  bool linhaDir = (c2 < limiarCalibracao);

  if (!linhaEsq && !linhaDir) {
    moverFrente(velocidadePWM);
  } 
  else if (linhaEsq && !linhaDir) {
    virarEsquerda(velocidadePWM);
  } 
  else if (!linhaEsq && linhaDir) {
    virarDireita(velocidadePWM);
  } 
  else {
    parar();
  }

  delay(10);
}
