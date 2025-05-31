#include <WiFi.h>

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define boardLED 2      // LED onboard
#define DHTPIN 12       // Pino de dados do DHT
#define DHTTYPE DHT22   // DHT22 (AM2302)
#define POTPIN 34       // Pino do potenciômetro (GPIO34/ADC6)

// Identificadores
const char* ID        = "quamtunLeap";
const char* moduleID  = "Meu_ESP32";

// Wi-Fi
const char* SSID      = "Wokwi-GUEST";
const char* PASSWORD  = "";

const char* BROKER_MQTT  = "172.208.54.189";
const int   BROKER_PORT  = 1883;
const char* mqttUser     = "gs2025";
const char* mqttPassword = "q1w2e3r4";

// Tópico MQTT
#define TOPICO_PUBLISH  "2TDS/esp32/teste"

WiFiClient espClient;
PubSubClient MQTT(espClient);
JsonDocument doc;  // Documento JSON dinâmico
char buffer[256];  // Buffer para o JSON serializado
DHT dht(DHTPIN, DHTTYPE);

float temperatura;
float umidade;
int valorPot;      // Valor do potenciômetro

void initWiFi() {
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Conectando ao Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void reconectaWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconectando Wi-Fi...");
        initWiFi();
    }
}

void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    while (!MQTT.connected()) {
        Serial.println("Conectando ao Broker MQTT...");
        if (MQTT.connect(moduleID, mqttUser, mqttPassword)) {
            Serial.println("Conectado ao Broker!");
        } else {
            Serial.print("Falha na conexão. Estado: ");
            Serial.println(MQTT.state());
            delay(2000);
        }
    }
}

void verificaConexoesWiFiEMQTT() {
    reconectaWiFi();
    if (!MQTT.connected()) {
        initMQTT();
    }
    MQTT.loop();
}

void enviaEstadoOutputMQTT() {
    MQTT.publish(TOPICO_PUBLISH, buffer);
    Serial.println("Mensagem publicada com sucesso!");
}

void piscaLed() {
    digitalWrite(boardLED, HIGH);
    delay(300);
    digitalWrite(boardLED, LOW);
}

void setup() {
    Serial.begin(115200);
    pinMode(boardLED, OUTPUT);
    pinMode(POTPIN, INPUT);
    digitalWrite(boardLED, LOW);
    dht.begin();
    initWiFi();    
    initMQTT();
}

void loop() {
    // Verifica e mantém conexões ativas com Wi-Fi e MQTT
    verificaConexoesWiFiEMQTT();

    // Leitura dos dados do sensor DHT
    umidade = dht.readHumidity();

    // Leitura do potenciômetro
    valorPot = analogRead(POTPIN);

    // Limpa o documento JSON para nova utilização
    doc.clear();

    // 1. Identificação
    doc["ID"] = ID;
    doc["Sensor"] = moduleID;

    // 2. Rede
    doc["IP"] = WiFi.localIP().toString();
    doc["MAC"] = WiFi.macAddress();

    // 3. Dados de sensores
    if (!isnan(umidade)) {
        doc["Umidade"] = umidade;
    } else {
        doc["Umidade"] = "Erro na leitura";
    }

    // 4. Dados do potenciômetro
    doc["Potenciometro"] = valorPot;

    // Serializa JSON para string
    serializeJson(doc, buffer);

    // Exibe no monitor serial
    Serial.println(buffer);

    // Envia via MQTT
    enviaEstadoOutputMQTT();

    piscaLed();

    delay(10000);
}