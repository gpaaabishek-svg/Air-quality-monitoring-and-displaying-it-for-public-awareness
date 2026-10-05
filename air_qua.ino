#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Pin Definitions ---
#define AIR_QUALITY_PIN A0   // MQ-135 connected to Analog A0
#define GREEN_LED 9          // Good Air Quality
#define RED_LED 8            // Poor Air Quality

// --- Objects ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Thresholds ---
const int AIR_QUALITY_THRESHOLD = 300;

void setup() {
  Serial.begin(9600);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality Mon.");

  delay(2000);
}

void loop() {
  // --- Read MQ-135 Sensor ---
  int airQualityValue = analogRead(AIR_QUALITY_PIN);

  lcd.clear();

  // --- Air Quality Display ---
  lcd.setCursor(0, 0);
  if (airQualityValue > AIR_QUALITY_THRESHOLD) {
    lcd.print("Air: POOR");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  } else {
    lcd.print("Air: GOOD");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }

  // --- Fixed Temperature & Humidity ---
  lcd.setCursor(0, 1);
  lcd.print("T:29C H:60%");

  // --- Debug Output ---
  Serial.print("Air Quality: ");
  Serial.print(airQualityValue);
  Serial.println(airQualityValue > AIR_QUALITY_THRESHOLD ? " | Air: POOR" : " | Air: GOOD");
  Serial.println("T:29C H:60%");

  delay(3000);
}
