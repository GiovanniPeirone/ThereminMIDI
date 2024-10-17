int distancia;
long tiempo;
int nota;
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
  distancia= int(0.0177*tiempo); //multiplicamos el tiempo para convertirlo en dista
  Serial.println(distancia);
  delay(100);
}
