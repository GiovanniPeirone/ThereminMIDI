int distancia;
long tiempo;
int nota;
void setup(){
  Serial.begin(9600);
  pinMode(12, OUTPUT); // trigger, aqui arduino envia un pulso al sensor, para que inicie la medicion
  pinMode(11, INPUT);  // echo, con este arduino recibe el pulso cuyo tiempo representa
                       //la duracion del viaje del sonido en el aire
}

void loop(){
  digitalWrite(12,LOW); 
  delayMicroseconds(5);
  digitalWrite(12, HIGH); //envio del pulso para iniciar medicion
  delayMicroseconds(10); //arduino espera 10 micro segundos
  tiempo=pulseIn(11, HIGH);  //se mide la duración del pulso
  distancia= int(0.0177*tiempo); //multiplicamos el tiempo para convertirlo en dista
  Serial.println(distancia);
  delay(500);
}
