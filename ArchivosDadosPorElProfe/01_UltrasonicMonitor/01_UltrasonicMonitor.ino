int distancia;
long tiempo;
int nota;
void setup(){
  Serial.begin(9600);
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
  distancia= int(0.0177*tiempo); //multiplicamos el tiempo para convertirlo en dista
  nota = map(distancia, 5, 60, 36, 60);
  Serial.println(distancia);
  Serial.write(144);
  Serial.write(nota);
  Serial.write(100);
  delay(100);
  Serial.write(144);
  Serial.write(nota);
  Serial.write(0);
  delay(50);
}
