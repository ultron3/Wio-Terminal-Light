#include <TFT_eSPI.h>

TFT_eSPI tft;
bool isLoading = true;  // Variabile per tenere traccia dello stato di caricamento

void setup() {
  tft.begin();
  tft.setRotation(3);  // Regola la rotazione del display se necessario
  tft.fillScreen(TFT_BLACK);
   pinMode(WIO_LIGHT, INPUT);// Sfondo nero
  showLoadingSpinner();
}

void loop() {
  if (isLoading) {
    showLoadingSpinner();
  } else {
    showBrightness();
  }
}

void showLoadingSpinner() {
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;
  int radius = 10;

  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);

  unsigned long startTime = millis();

  while (millis() - startTime < 50000) {  // Carica per 50 secondi
    tft.fillScreen(TFT_BLACK);

    for (int i = 0; i < 360; i += 30) {
      float radians = radians(i);
      int x = centerX + cos(radians) * radius;
      int y = centerY + sin(radians) * radius;

      tft.fillCircle(x, y, 3, TFT_WHITE);
    }

    tft.setCursor(centerX - 30, centerY + radius + 10);  // Posiziona il testo sotto la rotella
    tft.print("Loading...");

    delay(50);  // Puoi regolare la velocità della rotazione
  }

  isLoading = false;  // Cambia lo stato a false dopo 50 secondi
}

void showBrightness() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(10, 10);
  tft.print("Brightness: ");  // Aggiungi qui il codice per ottenere e visualizzare la luminosità
  tft.println(analogRead(WIO_LIGHT));
  // Puoi utilizzare ad esempio analogRead() per leggere un sensore di luminosità
  // Ottieni e stampa la data e l'ora correnti

  delay(5000);  // Aggiusta il ritardo in base alle tue esigenze
  isLoading = true;  // Torna allo stato di caricamento
}
