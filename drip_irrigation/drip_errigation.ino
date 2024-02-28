#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address 0x27 for a 16 chars and 2 line display

// Define the pin for the relay
const int relayPin_Pump = 5; 
const int relayPin_Solenoid1 = 6;
const int relayPin_Solenoid2 = 7;

// Define the threshold value for soil moisture, adjust as needed
const int moistureThreshold = 1000; 

const int sensor1Pin = A0; // Connect first soil moisture sensor to Analog pin A0
const int sensor2Pin = A1; // Connect second soil moisture sensor to Analog pin A1

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();

  // Initialize relay pin as output
  pinMode(relayPin_Pump, OUTPUT);
  pinMode(relayPin_Solenoid1, OUTPUT);
  pinMode(relayPin_Solenoid2, OUTPUT);

  digitalWrite(relayPin_Pump, HIGH);

}

void loop() {
  // Read soil moisture values from both sensors
  int moisture1 = analogRead(sensor1Pin);
  int moisture2 = analogRead(sensor2Pin);

  // Display the soil moisture readings on LCD
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("-PADIS-");
  //lcd.print(moisture1);
  //lcd.setCursor(0, 1);
  //lcd.print("Pump: ");
  //lcd.print(moisture2);

  if (moisture2 < moistureThreshold && moisture1 < moistureThreshold ) {
    digitalWrite(relayPin_Pump, HIGH);
     
    digitalWrite(relayPin_Solenoid2, HIGH);
    digitalWrite(relayPin_Pump, HIGH);
     digitalWrite(relayPin_Solenoid1, HIGH);
     lcd.setCursor(0, 1);
    lcd.print("Valve 1 & 2: OFF ");
}else

  // Check if either sensor detects dry soil
  if (moisture1 < moistureThreshold) {
    //lcd.clear();
    // If dry soil is detected, activate the relay
    digitalWrite(relayPin_Pump, HIGH);
    digitalWrite(relayPin_Solenoid1, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Pump 1: OFF 100%");
    
  }else if (moisture2 < moistureThreshold) {
   // Check if either sensor detects dry soil
    // If dry soil is detected, activate the relay
    digitalWrite(relayPin_Pump, HIGH);
    digitalWrite(relayPin_Solenoid2, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Pump 2: OFF 100% ");
    
  }else if (moisture2 > moistureThreshold || moisture1 > moistureThreshold ) {
    digitalWrite(relayPin_Pump, LOW);
     
    digitalWrite(relayPin_Solenoid2, LOW);
    digitalWrite(relayPin_Pump, LOW);
     digitalWrite(relayPin_Solenoid1, LOW);
     lcd.setCursor(0, 1);
    lcd.print("Valve 1 & 2: ON ");
} 
   /**
  if (moisture2 < moistureThreshold) {
   // Check if either sensor detects dry soil
    // If dry soil is detected, activate the relay
    digitalWrite(relayPin_Pump, HIGH);
    digitalWrite(relayPin_Solenoid2, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Pump 2: OFF ");
  } else{
    digitalWrite(relayPin_Pump, LOW);
     
    digitalWrite(relayPin_Solenoid2, LOW);
  }
  
  
  
 
  if (moisture2 < moistureThreshold || moisture1 < moistureThreshold ) {
   // Check if either sensor detects dry soil
    // If dry soil is detected, activate the relay
    digitalWrite(relayPin_Pump, HIGH);
    digitalWrite(relayPin_Solenoid1, HIGH);
    
    digitalWrite(relayPin_Pump, HIGH);
    digitalWrite(relayPin_Solenoid2, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Pump: OFF ");
  }else {
    //If soil is moist, de-activate the relay
      //digitalWrite(relayPin_Pump, LOW);
    digitalWrite(relayPin_Solenoid1, LOW);
      //lcd.setCursor(0, 1);
      //lcd.print("Pump 1: OFF");
    
    // If soil is moist, deactivate the relay
    digitalWrite(relayPin_Pump, LOW);
     digitalWrite(relayPin_Solenoid1, LOW);
    digitalWrite(relayPin_Solenoid2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Pump: ON");
  }
  **/
  delay(500); // Delay to stabilize readings
}
