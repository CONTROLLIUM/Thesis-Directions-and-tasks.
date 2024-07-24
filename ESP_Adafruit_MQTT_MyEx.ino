#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

// Credenciales Red WiFi
#define WIFI_SSID "CONTROLLIUM"
#define WIFI_PASSWORD "*******"
// Credenciales Adafruit
#define ADAFRUIT_USER "*****"
#define ADAFRUIT_KEY "******"
// Servidor
#define ADAFRUIT_SERVER "io.adafruit.com"
#define ADAFRUIT_PORT 1883
char ADAFRUIT_ID[30];
// Publicar
#define ADAFRUIT_FEED_HUM ADAFRUIT_USER "/feeds/Dato1"
#define ADAFRUIT_FEED_TEM ADAFRUIT_USER "/feeds/Dato2"
// Suscripción
#define ADAFRUIT_DATA_IN ADAFRUIT_USER "/feeds/data_in"

#define DHTPIN 4
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
float ValHum, ValTem = 0;

#define pin_led 2

//**********************************
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;

void setup_wifi();
// void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void mqtt_publish(String feed, int val);
void get_MQTT_ID();

void setup()
{
    Serial.begin(115200);
    delay(10);

    pinMode(pin_led, OUTPUT);
    digitalWrite(pin_led, LOW);

    get_MQTT_ID();
    setup_wifi();
    client.setServer(ADAFRUIT_SERVER, ADAFRUIT_PORT);
    // client.setCallback(callback);

    dht.begin(); // Inicializa el sensor dht

    digitalWrite(pin_led, HIGH);
    delay(200);
    digitalWrite(pin_led, LOW);
    delay(200);
    digitalWrite(pin_led, HIGH);
    delay(200);
    digitalWrite(pin_led, LOW);
    delay(200);
    digitalWrite(pin_led, HIGH);
    delay(200);
    digitalWrite(pin_led, LOW);
    delay(200);
    digitalWrite(pin_led, HIGH);
    delay(200);
    digitalWrite(pin_led, LOW);
    delay(200);
}

void loop()
{

    if (!client.connected())
    {
        reconnect();
    }

    client.loop();

    long now = millis();

    if (now - lastMsg > 4500)
    {
        lastMsg = now;

        ValHum = random(2, 90); // dht.readHumidity();
        ValTem = random(2, 200); // dht.readTemperature();

        if (isnan(ValHum) || isnan(ValTem))
        {
            ValHum = 0;
            ValTem = 0;
            Serial.println(F("Error de lectura del sensor DHT22!"));
        }

        Serial.print("Humedad: ");
        Serial.print(ValHum);
        Serial.print("%  Temperatura: ");
        Serial.print(ValTem);
        Serial.println("°C");

        // Publicar
        mqtt_publish(ADAFRUIT_FEED_HUM, ValHum);
        mqtt_publish(ADAFRUIT_FEED_TEM, ValTem);
    }
}

// Función para Publicar por MQTT
void mqtt_publish(String feed, int val)
{
    String value = String(val);
    if (client.connected())
    {
        client.publish(feed.c_str(), value.c_str());
        Serial.println("Publicando al tópico: " + String(feed) + " | mensaje: " + value);
    }
}

void setup_wifi()
{
    delay(10);

    // Nos conectamos a nuestra red Wifi AP
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(String(WIFI_SSID));

    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.println(".");
    }

    Serial.println("");
    Serial.println("Conectado a red WiFi!");
    Serial.println("Dirección IP: ");
    Serial.println(WiFi.localIP());
}
/*
// Función para capturar datos por MQTT
void callback(char *topic, byte *payload, unsigned int length)
{
    String mensaje  = "";
    String str_topic(topic);

    for (uint16_t i = 0; i < length; i++){
        mensaje += (char)payload[i];
    }

    mensaje.trim();

    Serial.println("Tópico: " + str_topic);
    Serial.println("Mensaje: " + mensaje);
}
*/
// Capturar el ChipID para Id de MQTT, esto es para que reconozca nuestro dispositivo, seguridad y esas cosas
void get_MQTT_ID()
{
    uint64_t chipid = ESP.getEfuseMac();
    snprintf(ADAFRUIT_ID, sizeof(ADAFRUIT_ID), "%llu", chipid);
}

void reconnect()
{
    while (!client.connected())
    {
        if (client.connect(ADAFRUIT_ID, ADAFRUIT_USER, ADAFRUIT_KEY))
        {
            Serial.println("MQTT conectado!");
            client.subscribe(ADAFRUIT_DATA_IN);
            Serial.println("Suscrito al tópico: " + String(ADAFRUIT_DATA_IN));
        }
        else
        {
            Serial.print("falló :( con error -> ");
            Serial.print(client.state());
            Serial.println(" Intentamos de nuevo en 5 segundos");
            delay(5000);
        }
    }
}
