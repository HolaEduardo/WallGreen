# <center>WallGreen</center>
<center>v1.0.0</center>

**Sistema de control de riego para jardines y muros verticales con controlador ESP-8266 / ESP-32**

WallGreen es un programa que automatiza la mantención de muros verdes. Las plantas se riegan cada 10 horas y con duración de 1 hora por riego. Además, el código leerá constantemente el nivel del agua en el bidón que almacena el agua de riego y encenderá o apagará la bomba en función de dicho nivel. De esta manera, garantizaremos que el muro verde se mantenga en las condiciones óptimas para su crecimiento y desarrollo. Este programa está optimizado para placa de desarrollo nodeMCU esp8266. Compilado en Arduino IDE.

### Hardware requerido
- nodeMCU 8266 v2/v3.
- Motherboard.
- Sensor de Temperatura DHT11 / DHT22, para éste caso, usaremos DHT22 por su alta precisión.
- Sensor de proximidad ultrasonico HC-SR04.
- Cableado.
- 2 Relés.
- Pantalla OLED 128x64 px. con adaptador I2C.

### Materiales requeridos
- Cableado para 220v/110v dependiendo de tu país.
- 2 tomas de corriente.
- Una bomba de agua potente (Rellenar bidón).
- Una bomba de agua normal (riego por goteo).
- Bidón para recolección de agua.
- Mangueras.

### Bibliotecas requeridas
- Biblioteca DHT para sensor de temperatura DHT11 y DHT22.
- Biblioteca Adafruit GFX.
- Biblioteca Adafruit SSD1306.

### Pines de conexión: 

- DHT22: DATA = D4.
- Sensor de proximidad:
trigger = D1, Echo = D2.
- relayBomba = D5.
- relayRiego = D6.
- Pantalla OLED: SDA = D2, SCL = D1.
- Energía: Todos los componentes deben conectarse de la siguiente manera: VCC = 3.3v o 5v (positivo), GND = GND (negativo). Idealmente, pantalla a 5v y sensores a 3.3v.

---

### *Características del código*

El código cuenta con 4 partes:

- Primera (lineas 1 a 45): Importamos las librería necesarias para el sensor y pantalla OLED. Creamos el objetos de la pantalla y sensor DHT. Definimos las constantes para la lectura de tiempo en milisegundos, considerando 2 constantes, una para el lapso entre riego de 10 horas, y otra para el tiempo de riego por 1 hora. Definimos los input e output digitales y análogos.

- Segunda (47 a 103): Setup(): Esta función inicia el programa y los componentes. Se configura la Serial del puerto en 115200 baudios. Este número debes ponerlo en el monitor serie para ver la salida en texto legible. Se inicia el display OLED 126x64 con adaptador I2C y se imprime un mensaje inicial que se mostrará cuando encendamos el nodeMCU. Definimos los pines de salida y entrada para el sensor de distancia y los reles. Iniciamos el sensor dht con la función dht.begin(). Enviamos un pulso de apagado al rele de la bomba y el riego para asegurarnos que éstas estén apagadas al iniciar el programa.

- Tercera (105 - 107): loop(): Esta función es la que se repetirá de forma continua mientras se ejecute el programa. Se llaman las funciones de la 4ta parte de éste código. Primero, lee el valor de la medición de agua y la guarda en una variable con tipo de dato de numero flotante. Este valor se usa posteriormente en la función controlBomba() usando como argumento la medición del sensor. Para finalizar, controlRiego verifica el tiempo transcurrido entre periodos de riego usando milisegundos como unidad de medida.

- Cuarta (145-264): Acá declaramos las funciones que serán llamadas en el loop. Consta de las siguientes 4 funciones.

    - readWaterLevel(): Función que lee la distancia entre el agua y el sensor. Si el agua traspasa la distancia especificada en esta función, se apagará o encenderá de acuerdo al caso.

    - readDHT22(): Lee la temperatura y humedad del aire. A pesar de no cumplir ninguna función más que imprimir esta información, en las próximas versiones se puede usar para control de clima junto a reles.

    - controlRiego(): Esta función cuenta con un contador que no se detiene cuando la función no se ejecuta, por lo tanto, en cada vuelta del loop, esta función lee el tiempo transcurrido, si este tiempo ha sido mayor a 10 horas, enciende la bomba de riego, luego, evalúa el tiempo transcurrido durante el riego, deteniendo luego de 1 hora la bomba de riego.

    - controlBomba(): Esta función evalúa en cada vuelta, la distancia del agua hacia el sensor, de acuerdo a la distancia especificada en la condicional, ésta se apagará o encenderá. Procura hacer pruebas si lo usarás, ya que los bidones tienen distinta distancia en su altura y ésto debe declararse en esta función.
    El programa esta hecho para que la bomba se encienda luego de que la medición marque 50 cm desde el sensor hasta el agua, encendiendo la bomba y reevaluando en cada loop si ésta debe ser apagada o no. Cuando la medición llega a 15 cm, la bomba se apaga, revisando en cada vuelta del loop la distancia y determinando si la bomba debe encenderse o apagarse.

---

### *Road-map proyecto*

>Objetivo general  

Crear un prototipo comercializable para el cuidado y mantención de jardines normales y verticales. Junto a una infraestructura que considere poder controlar estos parámetros mediante una API. Además, por una parte de hardware, el objetivo considera el diseño de PCB personalizada para los fines de este proyecto y presentar ante eventuales inversionistas, un prototipo usable al 80% de sus funciones.

>Objetivos específicos 

Nuestros objetivos específicos se dividirán en 3 fases de desarrollo

Fase 1: v1.x.x: El objetivo es crear y testear un sistema autónomo de riego por goteo para muros verticales. Considerando impresión por pantalla OLED los procesos del programa.

Fase 2: v2.x.x: Agregar servidor HTTP. En esta fase, configuraremos el nodeMCU para funcionar como servidor HTTP, enviando y recibiendo peticiones GET y POST para controlar las variables, los tiempos y enviar información del programa para visualizar en plataforma web. Esta fase, también incluye una plataforma web pequeña que considere al menos 3 tipos de peticiones y muestre la información de los sensores en la plataforma.

Fase 3: v3.x.x: Vincular el programa a un dominio dinámico. Hacía el cual direccionaremos las peticiones a traves de un Proxy Reverse. Apuntado desde nuestro dominio con ip fija hacia nuestro dominio con ip dinámica que usará el nodeMCU. Durante esta fase, se debe testear el programa probando todas sus iteraciones y mezcla de ellas. Para finalizar, terminaremos el diseño de plataforma a un interfaz de usuario atractivo y fácil de usar.

Fase 4: Durante esta fase, analizaremos los factores legales para patentar el diseño y funcionamiento del programa y la PCB. Revisaremos los costos de producción y estimaremos un flujo de caja en relación a estimaciones de venta. Estimaremos la valuación total del proyecto y nuestros porcentajes de participación. Con el fin de presentar una oferta clara. Teniendo esta información , buscaremos inversionistas que se interesen en el proyecto y fondos públicos que puedan financiar la puesta en marcha.

Nota*: Las funciones que implementes, deben ser declaradas fuera del loop y llamadas a este. Para mantener la eficiencia del código, su modularidad y su correcto funcionamiento.

Si estás invitado a este repositorio, significa que estás invitado/a a ser parte de este proyecto. De acuerdo avancemos. Se evaluará de buena manera y bajo mutuo acuerdo los porcentajes de participación en caso de inversión. Siendo valuados principalmente en el tiempo invertido para finalizar todas cada una de las fases.