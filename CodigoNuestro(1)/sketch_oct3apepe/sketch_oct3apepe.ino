// Definición de pines para el sensor ultrasónico
int Trig = 13; // Pin de disparo (Trig)
int Echo = 12; // Pin de eco (Echo)
const int  PinReservado = 13;

void setup()s
{
    Serial.begin(9600); // Inicializa la comunicación serie a 9600 baudios
    pinMode(Trig, OUTPUT); // Configura el pin Trig como salida
    pinMode(Echo, INPUT); // Configura el pin Echo como entrada
    pinMode(Echo, INPUT);
}

void loop ()
{
    int duracion; // Variable para almacenar la duración del pulso
    float distancia; // Variable para almacenar la distancia calculada

    // Enviamos un pulso de 10 microsegundos al pin Trig para activar el sensor
    digitalWrite(Trig, LOW); // Aseguramos que el pin Trig esté bajo
    delayMicroseconds(4); // Esperamos 4 microsegundos
    digitalWrite(Trig, HIGH); // Activamos el pin Trig
    delayMicroseconds(10); // Mantenemos el pulso alto durante 10 microsegundos
    digitalWrite(Trig, LOW); // Desactivamos el pin Trig

    // Medimos el tiempo que tarda el eco en regresar al pin Echo
    duracion = pulseIn(Echo, HIGH); // Lee el pulso en el pin Echo

    // Dividimos la duración por 2 porque el tiempo registrado es de ida y vuelta
    duracion = duracion / 2;

    // Calculamos la distancia en centímetros (1 microsegundo es aproximadamente 0.034 cm)
    distancia = duracion / 29; // La fórmula es distancia = tiempo / 29 (para cm)

    // Enviamos la distancia calculada a través del puerto serie
    Serial.println(distancia); // Corrigiendo el nombre de la variable 'distancia'

    delay(50); // Esperamos 50 ms antes de realizar la siguiente lectura
}