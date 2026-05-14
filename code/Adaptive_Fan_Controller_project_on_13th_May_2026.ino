#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float temp;

// Relay pin
int relayPin = 7;

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  pinMode(relayPin, OUTPUT);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Fan System");

  delay(2000);
  lcd.clear();

  Serial.begin(9600);
}

void loop() {

  // Read temperature
  temp = dht.readTemperature();

  // Check sensor first
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error   ");
    lcd.setCursor(0, 1);
    lcd.print("Check DHT11    ");
    return;
  }

  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C   ");

  Serial.print("Temperature: ");
  Serial.println(temp);

  // Fan control
  if (temp > 31) {
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Fan: ON  ");
  } 
  else {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fan: OFF ");
  }

  delay(2000);
}