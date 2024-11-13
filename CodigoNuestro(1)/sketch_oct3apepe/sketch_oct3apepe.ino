int Trig1 = 12; // Pin Trigger para el sensor 1 (notas)
int Echo1 = 13; // Pin Echo para el sensor 1 (notas)
int Trig2 = 10; // Pin Trigger para el sensor 2 (volumen)
int Echo2 = 9;  // Pin Echo para el sensor 2 (volumen)
const int VCC2 = 7;  // VCC del segundo sensor en el pin digital 7

const int notas[] = {36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 53, 55, 57, 59, 60}; // Notas MIDI discretas
const int numNotas = sizeof(notas) / sizeof(notas[0]); // Cantidad de notas en el array
const int distanciaMin = 5;   // Distancia mínima en cm
const int distanciaMax = 60;  // Distancia máxima en cm

float distancia1, distanciaAnterior1;
float distancia2, distanciaAnterior2;
long tiempo1, tiempo2;
int nota;
int volumen;

void setup() {
  Serial.begin(9600);          // Inicializa la comunicación en serie
  
  // Configuración del primer sensor
  pinMode(Trig1, OUTPUT);      
  pinMode(Echo1, INPUT);

  // Configuración del segundo sensor
  pinMode(Trig2, OUTPUT);      
  pinMode(Echo2, INPUT);

  // Alimentar el segundo sensor desde el pin digital 7
  pinMode(VCC2, OUTPUT);
  digitalWrite(VCC2, HIGH); // Activa el VCC para el segundo sensor
}

void loop() {
  // Medición del primer sensor para las notas
  digitalWrite(Trig1, LOW); 
  delayMicroseconds(5);
  digitalWrite(Trig1, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Trig1, LOW);
  tiempo1 = pulseIn(Echo1, HIGH);  
  distancia1 = 0.0177 * tiempo1;

  // Si la distancia cambia más de 0.8 cm
  if (abs(distanciaAnterior1 - distancia1) > 0.8) { 
    if (distancia1 <= distanciaMax) {
      int notaIndex = map(distancia1, distanciaMin, distanciaMax, 0, numNotas - 1);
      nota = notas[notaIndex];

      Serial.write(144);  // "Note On" en canal 1
      Serial.write(nota); 
      Serial.write(100);  // Velocidad de la nota (100 de 127)

      delay(100); // Mantener la nota un momento

      Serial.write(144);  // "Note Off" en canal 1
      Serial.write(nota); 
      Serial.write(0);    // Velocidad de apagado (0 = apagado)
    }
    distanciaAnterior1 = distancia1;
  }

  // Medición del segundo sensor para el volumen
  digitalWrite(Trig2, LOW); 
  delayMicroseconds(5);
  digitalWrite(Trig2, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Trig2, LOW);
  tiempo2 = pulseIn(Echo2, HIGH);  
  distancia2 = 0.0177 * tiempo2;

  // Si la distancia cambia más de 0.8 cm
  if (abs(distanciaAnterior2 - distancia2) > 0.8) { 
    if (distancia2 <= distanciaMax) {
      volumen = map(distancia2, distanciaMin, distanciaMax, 0, 127);
      volumen = constrain(volumen, 0, 127); // Limitar el valor de volumen entre 0 y 127

      Serial.write(176);  // "Control Change" en canal 1
      Serial.write(7);    // Control Change para volumen (CC número 7)
      Serial.write(volumen);  // Valor de volumen mapeado
    }
    distanciaAnterior2 = distancia2;
  }

  delay(120);  // Pausa antes de la próxima lectura
}
