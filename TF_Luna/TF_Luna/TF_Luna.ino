/* Based on Bud Ryerson: TFLI2C_simple.ino
 * Described: Simplified Arduino example sketch for the Benewake
 * TF-Luna Lidar sensor configured for the serial interface
 */
 
#include <Arduino.h>     // Every sketch needs this
//#include <Wire.h>        // Instantiate the Wire library
#include <HardwareSerial.h>

// Connect TF Luna pin 5 to 3.3V or disconnct it for Serial mode
// Define RX/TX pins for ESP32
#define RX_PIN 16  // Change to your desired RX pin on ESP32
#define TX_PIN 17  // Change to your desired TX pin on ESP32

HardwareSerial LiDAR(2);  //
const int thresholdDistance = 100;  // Object detection Threshold value (100cm)

void setup() {
  Serial.begin(115200);
  LiDAR.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);  // Baud, serial mode, RX, TX

  Serial.println("TFmini Plus LiDAR - object detection ready");
}

void loop() {
  if (LiDAR.available() >= 9) {  // TFmini sends data in 9-byte packets
    uint8_t data[9];
    for (int i = 0; i < 9; i++) {
      data[i] = LiDAR.read();
    }

    if (data[0] == 0x59 && data[1] == 0x59) {  // Checkmarks
      int distance = data[2] + (data[3] << 8);  // Distance in cm
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      if (distance < thresholdDistance) {
        Serial.println("Object detected!");
        // add you own logic here
      }
    }
  }
}
