# Diseño de una red de sensores para medir vibraciones de motores en la industria 

### **Hardware**  
#### Materiales a utilizar

* Microcontrolador ESP8266
* Módulo Acelerómetro
* SBC Raspberry Pi

#### ¿Cómo va a estar confeccionada la red?

Los datos de las mediciones serán sensados con los modulos de acelerómetro conectados a los ESP8266 donde los mismos van a enviar los datos a una Raspberry Pi donde se visualizarán, es decir, cada modulo de acelerómetro con su respectivo ESP8266 donda cada microcontrolador enviará los datos a una pagina web en una Raspberry Pi donde se van a visualizar los datos de cada uno de los ejes (X)(Y)(Z), los tiempos , la temperatura y un historial para poder ver los datos anteriores, todo eso en cada motor. Es necesario tener en cuanta como se trata de un proyecto con visión futurista de aplicación es necesario realizar en la paquina web un control de acceso con toda la capa de seguridad pertinente. También toda la configuracion de los equipos para la posible conección con la Raspberry Pi.

#### ¿Por qué usar un ESP8266 y no un ESP32?

Como se quiere solamente utilizar el Wi-Fi integrado en el microcontrolador y leer via TWI (Two Wireless Interface o I2C) los datos del módulo acelerómetro, no es necesario utilizar un microcontrolador tan potente como el ESP32 , ya que su antecesor el ESP8266 es idóneo para esta aplicación de lectura y transmisión de datos. 

#### **Software** 

* Raspberry Pi
    *  Lenguaje Python
        * *Flask*
        * *Django* 
* ESP8266
    *  Lenguaje C/C++

#### ¿Qué protocolo utilizar?
MQTT ya que es un protocolo de red ligero de máquina a máquina, de publicación y suscripción, para colas de mensajes y servicios de cola de mensajes. Está diseñado para conexiones con ubicaciones remotas que tienen dispositivos con limitaciones de recursos o ancho de banda de red limitado, como en el Internet de las cosas.

#### Etapa investigativa
* Buscar 
    * *tesis o ariculos que tengan que ver con esta misma temática.*
    * *Lugar, ventajas , tecnologias que utilizaron, desventajas.*

Realizar un resumen de todos los aspectos de relevancia.

#### Contacto:
[+53 51259172]()
[luismiguelechevarriarodriguez@gmail.com]()
[luismigec@automatica.cujae.edu.cu]()
