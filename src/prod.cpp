// Importamos liberias necesarias para conectar el ESP8266 a la red WiFi y crear un servidor HTTP
//#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
// Importamos liberia de sensor DHT22
#include <DHT.h>

// Importamos liberia adafruit para pantalla OLED de 128x64
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Configura tu red WiFi
//const char* ssid = "your_SSID";
//const char* password = "your_PASSWORD";

// Definimos el pin de la pantalla OLED
//#define OLED_RESET 16 // D0

// Creamos objeto de la pantalla OLED * Agregar reset pin en caso de usar, agregarlo en el constructor al final como ", OLED_RESET"
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


// Definimos pin para sensor DHT22
#define DHTPIN 2 // D4
// Definimos tipo de sensor DHT22
#define DHTTYPE DHT22
// Creamos objeto DHT
DHT dht(DHTPIN, DHTTYPE);

// Define los pines para el sensor de distancia
const int trigPin = 5; // D1
const int echoPin = 4; // D2
// Define los pines para el relé que controla la bomba de agua y el relé que controla el riego
const int relayBomba = 14; // D5
const int relayRiego = 12; // D6

// Configura el tiempo de intervalo de riego cada 10 horas
const unsigned long wateringInterval = 10 * 60 * 60 * 1000; // 10 horas
// Configura el tiempo de riego cada 1 hora
const unsigned long wateringDuration = 1 * 60 * 60 * 1000; // 1 hora
// Guarda el tiempo actual en milisegundos inicialmente en 0
unsigned long previousMillis = 0;
// Define el estado de la bomba de agua en false por defecto
bool isWatering = false;
// Crea un servidor HTTP en puerto 80
//ESP8266WebServer server(80);

// Función de configuración para nodeMCU
void setup() {

  // Inicia la comunicación serial en 115200 baudios
  Serial.begin(115200);

  // Inicia la pantalla OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Iniciando...");
  display.display();

  // Configura los pines como salida o entrada del sensor de distancia
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configura el pin del relé como salida
  pinMode(relayBomba, OUTPUT);
  pinMode(relayRiego, OUTPUT);

  // Inicia el sensor DHT22
  dht.begin();

  // Apaga la bomba de agua y el riego al iniciar
  digitalWrite(relayBomba, LOW);
  digitalWrite(relayRiego, LOW);

  // Conexión a la red WiFi
  //Serial.print("Conectando a ");
  //Serial.println(ssid);
  //WiFi.begin(ssid, password);

  // Mientras no se conecte a la red WiFi
  //while (WiFi.status() != WL_CONNECTED) {
    // Imprimir un punto en la consola para indicar que se está intentando conectar cada 500 milisegundos
    //Serial.print(".");
    // Espera delay de 500 milisegundos
    //delay(500);
  //}
  // Una vez conectado a la red WiFi, imprime la dirección IP y mensaje de conexión exitosa
  //Serial.println("");
  //Serial.println("WiFi conectado");
  //Serial.println("Dirección IP: ");
  //Serial.println(WiFi.localIP());

  // Configura la API
  // Iniciamos el servidor HTTP
  //server.begin();
  //Serial.println("Servidor HTTP iniciado");

  // Endpoint para obtener el nivel de agua
  //server.on("/estado", handleEstado);
  // Otros endpoints
}

// Función de loop para nodeMCU
void loop() {
  // Verifica si hay peticiones HTTP
  //server.handleClient();

  // Leemos y enviamos el nivel de agua por serial y lo guardamos en la variable waterLevel
  float waterLevel = readWaterLevel();

  // Verifica si hay que encender o apagar la bomba de agua e incluimos la lectura del sensor de distancia
  controlBomba(waterLevel);

  // Verifica si hay que encender o apagar el riego
  controlRiego();
}

void readDHT22() {
  // Lee la temperatura y humedad del sensor DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Imprime la temperatura y humedad en la consola
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print("°C, Humedad: ");
  Serial.print(h);
  Serial.println("%");
  // Imprime la temperatura y humedad en la pantalla OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Temperatura: ");
  display.println(t);
  display.println("°C");
  display.println("Humedad: ");
  display.println(h);
  display.println("%");
  display.display();
}


// Función para leer el nivel de agua
float readWaterLevel() {
  // Envía un pulso de ultrasonido cada 2 segundos
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Espero 10 microsegundos para enviar el pulso de ultrasonido
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  // Envía el pulso de ultrasonido
  digitalWrite(trigPin, LOW);

  // Lee el tiempo que tarda en recibir el pulso de ultrasonido
  float duration = pulseIn(echoPin, HIGH);
  // Calcula la distancia en centímetros
  float distance = duration * 0.034 / 2;
  
  // Imprime la distancia en la consola
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Imprime la distancia en la pantalla OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Distancia: ");
  display.println(distance);
  display.println("cm");
  display.display();

  // Retorna la distancia en tipo de dato float
  return distance;
}
// Función para controlar la bomba de agua
void controlBomba(float waterLevel) { 
  // currentMillis guarda el tiempo actual en milisegundos
  unsigned long currentMillis = millis();
  // Si el nivel de agua es menor a 10 cm, enciende la bomba de agua
  if (waterLevel >= 50) {
    // Enciende la bomba de agua
    digitalWrite(relayBomba, LOW);
    // Imprime en la consola que la bomba de agua está encendida
    Serial.println("Bomba de agua encendida");

    // Imprime en la pantalla OLED que la bomba de agua está encendida
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Bomba de agua");
    display.println("encendida");
    display.display();
 
    // Si el nivel de agua es mayor a 60 cm, apaga la bomba de agua
  } else if (waterLevel <= 15) {
     // Apaga la bomba de agua
    digitalWrite(relayBomba, LOW);
    // Imprime en la consola que la bomba de agua está apagada
    Serial.println("Bomba de agua apagada");

    // Imprime en la pantalla OLED que la bomba de agua está apagada
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Bomba de agua");
    display.println("apagada");
    display.display();
  }
}

void controlRiego() {
  // Si la bomba de agua está encendida, verifica si ya ha pasado el tiempo de riego
  if (isWatering) {
    // Si ya ha pasado el tiempo de riego, apaga la bomba de agua
    if (millis() - previousMillis >= wateringDuration) {
       // Apaga la bomba de agua
      digitalWrite(relayRiego, LOW);

      // Imprime en la consola que la bomba de agua está apagada
      Serial.println("Riego terminado");

      // Imprime en la pantalla OLED que la bomba de agua está apagada
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Riego");
      display.println("apagado");
      display.display();
      // Cambia el estado de la bomba de agua
      isWatering = false;
      // Guarda el tiempo actual en milisegundos
      previousMillis = millis();
    }
  } else {
    // Si la bomba de agua está apagada, verifica si ya ha pasado el intervalo de riego
    if (millis() - previousMillis >= wateringInterval) {
       // Enciende la bomba de agua
      digitalWrite(relayRiego, HIGH);

      // Imprime en la consola que la bomba de agua está encendida
      Serial.println("Riego encendido");

      // Imprime en la pantalla OLED que la bomba de agua está encendida
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Riego");
      display.println("encendido");
      display.display();

      // Cambia el estado de la bomba de agua a encendida/true
      isWatering = true;
      // Guarda el tiempo actual en milisegundos
      previousMillis = millis();
    }
  }
}