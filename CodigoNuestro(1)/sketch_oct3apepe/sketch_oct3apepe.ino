int Trig = 9; // Pin de disparo (Trigger)
int Echo = 8; // Pin de eco (Echo)
const int notaMin = 36;  // Nota MIDI mínima (C2)
const int notaMax = 60;  // Nota MIDI máxima (C4)
const int distanciaMin = 5;   // Distancia mínima en cm
const int distanciaMax = 60;  // Distancia máxima en cm
float distancia, distanciaAnterior;
long tiempo;
int nota;

void setup() {
  Serial.begin(9600);          // Inicializa la comunicación en serie
  pinMode(Trig, OUTPUT);        // Configura el pin Trig como salida
  pinMode(Echo, INPUT);         // Configura el pin Echo como entrada
}

void loop() {
  // Envía un pulso al sensor para iniciar la medición
  digitalWrite(Trig, LOW); 
  delayMicroseconds(5);
  digitalWrite(Trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW);

  // Mide la duración del pulso en el pin Echo
  tiempo = pulseIn(Echo, HIGH);  
  distancia = 0.0177 * tiempo;   // Convierte el tiempo en distancia (cm)

  // Solo enviar notas cuando la distancia cambia más de 0.8 cm
  if (abs(distanciaAnterior - distancia) > 0.8) { 
    if (distancia <= distanciaMax) {
      // Mapear la distancia a un valor de nota MIDI
      nota = map(distancia, distanciaMin, distanciaMax, notaMin, notaMax);
      nota = constrain(nota, notaMin, notaMax); // Limitar al rango de notas

      // Enviar "Note On" para activar la nota en BandLab
      Serial.write(144);  // "Note On" en canal 1
      Serial.write(nota); // Nota calculada
      Serial.write(100);  // Velocidad de la nota (100 de 127)

      delay(100); // Mantener la nota un momento

      // Enviar "Note Off" para desactivar la nota en BandLab
      Serial.write(144);  // "Note Off" en canal 1
      Serial.write(nota); // Nota calculada
      Serial.write(0);    // Velocidad de apagado (0 = apagado)
    }
    distanciaAnterior = distancia;
  }

  delay(50);  // Pausa antes de la próxima lectura
}
