// AudioControlSystem_DualEncoder.ino

#include <Encoder.h>

// Rotary encoders
Encoder volumeEncoder(2, 3); // Pins connected to the volume encoder
Encoder menuEncoder(4, 5);   // Pins connected to the menu encoder

// Variables to store the position of each encoder
long volumePosition = 0;
long menuPosition = 0;

void setup() {
    Serial.begin(9600); // Initialize serial communication
}

void loop() {
    // Read volume encoder value
    long newVolumePosition = volumeEncoder.read();
    if (newVolumePosition != volumePosition) {
        volumePosition = newVolumePosition;
        Serial.print("Volume Position: ");
        Serial.println(volumePosition);
    }

    // Read menu encoder value
    long newMenuPosition = menuEncoder.read();
    if (newMenuPosition != menuPosition) {
        menuPosition = newMenuPosition;
        Serial.print("Menu Position: ");
        Serial.println(menuPosition);
    }

    delay(100); // Small delay to avoid overwhelming the Serial output
}