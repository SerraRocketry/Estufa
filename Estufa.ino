#include <LiquidCrystal.h>
# include <Adafruit_Sensor.h>
# include <DHT.h>
# include <DHT_U.h>

# define DHTPIN 8    // Digital pin connected to the DHT sensor 

# define DHTTYPE    DHT22     // DHT 22 (AM2302)

// Define the pins that will be used for LCD connection
LiquidCrystal lcd(2,3,4,5,6,7);

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {

  // Initialize serial communication
  Serial.begin(9600);

  // Initialize LCD screen
  lcd.begin(16, 2);

  // Initialize DHT sensor
  dht.begin();  

  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));

  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);

  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));

  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

}

void loop() {
  
  delay(delayMS);

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    lcd.print("Error reading temperature!");  
  }
  else {

    lcd.setCursor(5, 0);    // set the cursor position

    // print a message to the LCD
    lcd.print(event.temperature); 
    lcd.print("C"); 
    Serial.print(F("Temperatura: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);

  if (isnan(event.relative_humidity)) {

    Serial.println(F("Error reading humidity!"));
    lcd.print("Error reading humidity!");  
    
  }
  else {
    
    lcd.setCursor(5, 1);     // set the cursor position

    // print a message to the LCD
    lcd.print(event.relative_humidity);       
    lcd.print("%"); 
    Serial.print(F("Umidade: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
  
  delay(1000);                    

}
