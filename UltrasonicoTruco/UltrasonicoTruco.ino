int Trig1 = 12;
int Echo1 = 13;
int Trig2 = 10;
int Echo2 = 9;
int VCC2 = 7;

// Notas de la escala de Do en la octava 1 (C1 a B1)
const int notas[] = {
  24, // C1
  26, // D1
  28, // E1
  29, // F1
  31, // G1
  33, // A1
  35  // B1
};

const int distanciaMin = 5, distanciaMax = 60, numNotas = sizeof(notas) / sizeof(notas[0]);
float distancia1, distanciaAnterior1, distancia2, distanciaAnterior2;
int notaActual, notaObjetivo, volumen;

void setup() {
  Serial.begin(9600);
  pinMode(Trig1, OUTPUT);
  pinMode(Echo1, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(VCC2, OUTPUT);
  digitalWrite(VCC2, HIGH);
}

void loop() {
  // Sensor de notas
  digitalWrite(Trig1, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig1, LOW);
  distancia1 = 0.0177 * pulseIn(Echo1, HIGH);

  if (abs(distanciaAnterior1 - distancia1) > 0.8 && distancia1 <= distanciaMax) {
    // Mapear la distancia a las notas de la escala de Do
    notaObjetivo = notas[map(distancia1, distanciaMin, distanciaMax, 0, numNotas - 1)];
    
    // Efecto de glissando
    if (notaActual < notaObjetivo) notaActual++;
    else if (notaActual > notaObjetivo) notaActual--;

    // Enviar nota MIDI
    Serial.write(144); Serial.write(notaActual); 
    Serial.write(100);
    delay(30);  // Pausa para el glissando
    Serial.write(144); Serial.write(notaActual); 
    Serial.write(0);
    distanciaAnterior1 = distancia1;
  }

  // Sensor de volumen
  digitalWrite(Trig2, LOW);
  delayMicroseconds(5);
  digitalWrite(Trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig2, LOW);
  distancia2 = 0.0177 * pulseIn(Echo2, HIGH);

  if (abs(distanciaAnterior2 - distancia2) > 0.8 && distancia2 <= distanciaMax) {
    // Mapear la distancia al rango de volumen MIDI (0-127)
    volumen = constrain(map(distancia2, distanciaMin, distanciaMax, 0, 127), 0, 127);
    
    // Enviar control MIDI para volumen
    Serial.write(176);
    Serial.write(7);
    Serial.write(volumen);
    distanciaAnterior2 = distancia2;
  }
}
