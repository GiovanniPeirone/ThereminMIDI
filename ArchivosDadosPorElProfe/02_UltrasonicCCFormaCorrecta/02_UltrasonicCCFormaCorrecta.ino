//Código hecho por Daniel Marcial (@danielmarcial22)
//Este código sirve para usar el sensor ultrasónico como un Control Change
//Con este código se puede modular cualquier parámetro en Ableton
// pin 9 - Trigger (naranja)
// pin 8 - Echo (azul)
// 5V    - Vcc (rojo
//GND    - GND (negro)
//Este código también funciona para controlar con la mano mientras el ultrasónico permanece recostado
const int aMin = 5; //altura mínima a mapear
const int aMax = 50; //altura máxima a mapear
float distancia,distanciaAnterior;
long tiempo;
int valor;
void setup(){
  Serial.begin(115200);
  pinMode(9, OUTPUT); // trigger, aqui arduino envia un pulso al sensor, para que inicie la medicion
  pinMode(8, INPUT);  // echo, con este arduino recibe el pulso cuyo tiempo representa
                       //la duracion del viaje del sonido en el aire
}

void loop(){
  digitalWrite(9,LOW); 
  delayMicroseconds(5);
  digitalWrite(9, HIGH); //envio del pulso para iniciar medicion
  delayMicroseconds(10); //arduino espera 10 micro segundos
  tiempo=pulseIn(8, HIGH);  //se mide la duración del pulso
  distancia= 0.0177*tiempo; //multiplicamos el tiempo para convertirlo en dista

  if (abs(distanciaAnterior-distancia)>0.8) //resolución de 8 mm.
  {
    if (distancia<=aMax+2)
    {
    valor = map(distancia,aMin,aMax,0,127); //mapear alturas mínima y máxima a valores de 0 a 127  
    if (valor>127) valor=127; //limiter
    if (valor<0) valor=0; //limiter para los negativos
    Serial.write(176);//Control Change canal 1
    Serial.write(30); // CC 30
    Serial.write(valor); //CC value
    }
    distanciaAnterior = distancia;
  }

  delay(5);
  
}
