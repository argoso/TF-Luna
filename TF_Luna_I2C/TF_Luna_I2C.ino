/* Based on Bud Ryerson: TFLI2C_simple.ino
 * Described: Simplified Arduino example sketch for the Benewake
 * TF-Luna Lidar sensor configured for the I2C interface
 */

#include <Arduino.h>     // every sketch needs this
#include <Wire.h>        // instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.2.0

TFLI2C tflI2C;

int16_t tfDist;          // Distance in centimeters
int16_t tfAddr = TFL_DEF_ADR;  // Default I2C address for TF Luna
const int thresholdDistance = 100;  // Object detection threshold (in cm)

// Connect TF Luna pin 5 to GND for I2C mode
// Define I2C pins for ESP32
#define I2C_SDA 17  // Change to your desired SDA pin
#define I2C_SCL 16  // Change to your desired SCL pin

void scanI2C() {
    Serial.println("Scanning I2C bus...");
    byte count = 0;
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found device at 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address, HEX);
            count++;
        }
    }
    if (count == 0) {
        Serial.println("No I2C devices found.");
    } else {
        Serial.print("Total devices found: ");
        Serial.println(count);
    }
    delay(5000); // 5sec to display result of scanning
}

void setup()
{
    Serial.begin(115200);              // Initialize serial port
    Wire.begin(I2C_SDA, I2C_SCL);      // Initialize Wire library with specific pins
    Serial.println("TFLI2C example code with object detection"); // say "Hello!"
    Serial.println("Modified for ESP32");

    scanI2C();  // Perform I2C bus scan
}

void loop()
{
    if (tflI2C.getData(tfDist, tfAddr)) // If read okay...
    {
        Serial.print("Distance: ");
        Serial.print(tfDist);
        Serial.println(" cm");

        // Object detection logic
        if (tfDist < thresholdDistance) {
            Serial.println("Object detected!");
            // Add your custom logic here, e.g., trigger an alarm or LED
        }
    }
    else 
    {
        tflI2C.printStatus();            // else, print error.
    }

    delay(50);
}
