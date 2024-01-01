#include <WiFi.h>
#include <WebSocketsServer.h>
#include <TFT_eSPI.h>

#define IOT_CONFIG_WIFI_SSID        "WebCube-A71D"
#define IOT_CONFIG_WIFI_PASSWORD    "2EE7C62J"
#define WEBSOCKET_SERVER_PORT       4001

TFT_eSPI tft;
WebSocketsServer webSocket = WebSocketsServer(WEBSOCKET_SERVER_PORT);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_TEXT: {
      // Ricevuto un messaggio di testo dal client WebSocket
      String receivedPayload = String((char*)payload);
      Serial.print("Received: ");
      Serial.println(receivedPayload);
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);

  tft.begin();
  pinMode(WIO_LIGHT, INPUT);
  tft.fillScreen(0x0);

  // Connessione WiFi
  WiFi.begin(IOT_CONFIG_WIFI_SSID, IOT_CONFIG_WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");

  // Inizia il server WebSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started");
}

void loop() {
  webSocket.loop();

  // Leggi il valore dalla luce
  int lightValue = analogRead(WIO_LIGHT);

  // Converti il valore in una stringa
  String payload = String(lightValue);

  // Aggiorna lo schermo con il valore della luce
  tft.fillScreen(0x481F); // Colore di sfondo
  tft.setTextSize(3);
  tft.setCursor(100, 50);
  tft.print(payload);

  // Invia il valore a tutti i client WebSocket
  webSocket.broadcastTXT(payload);

  // Stampa il valore sulla porta seriale
  Serial.println("Light Value: " + payload);

  delay(1000);  // Attendi un secondo prima di inviare nuovamente i dati
}
