#include "TinyGPS++.h"
#include "SoftwareSerial.h"

SoftwareSerial serial_connection(5, 6); // tx,rx
TinyGPSPlus gps; // GPS object to process the NMEA data

bool getUserChoice() {
  Serial.println("Do you want to get location again? (y/n)");
  while (!Serial.available()) {
    // Wait for user input
  }
  char choice = Serial.read();
  Serial.println(); // Move to the next line
  return (choice == 'y' || choice == 'Y');
}

void setup() {
  Serial.begin(9600);               // This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);    // This opens up communications to the GPS
  Serial.println("GPS Start");       // To show in the serial monitor that the sketch has started
}

void loop() {
  while (serial_connection.available()) // While there are incoming characters from the GPS
  {
    gps.encode(serial_connection.read()); // This feeds the serial NMEA data into the library one char at a time
  }

  if (gps.location.isUpdated()) // This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    // Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.print("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude:");
    Serial.println(gps.location.lng(), 6);

    Serial.print("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");

    Serial.print("Date: ");
    if (gps.date.isValid()) {
      Serial.print(gps.date.month());
      Serial.print("/");
      Serial.print(gps.date.day());
      Serial.print("/");
      Serial.println(gps.date.year());
    }

  Serial.print("Time: ");
if (gps.time.isValid()) {
  int WIB_offset = 7; // Waktu Indonesia Barat (UTC+7)
  int localHour = (gps.time.hour() + WIB_offset) % 24;

  if (localHour < 10) Serial.print(F("0"));
  Serial.print(localHour);
  Serial.print(":");
  if (gps.time.minute() < 10) Serial.print(F("0"));
  Serial.print(gps.time.minute());
  Serial.print(":");
  if (gps.time.second() < 10) Serial.print(F("0"));
  Serial.print(gps.time.second());
  Serial.print(".WIB");
}
Serial.println("");


    if (!getUserChoice()) {
      while (true) {
        // Stay in this loop if user chooses not to get location again
      }
    }
  }
}
