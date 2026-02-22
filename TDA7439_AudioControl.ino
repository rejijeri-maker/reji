#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <Rotary.h>

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Rotary rotary = Rotary(2, 3); // Assuming pins 2 and 3 for rotary encoder

int currentInput = 0;
int toneSettings[5]; // Assume 5 frequency bands for tone control
const int maxInputs = 3; // Example of maximum inputs

void setup() {
    display.begin(SSD1306_I2C_ADDRESS, OLED_RESET);
    display.clearDisplay();
    loadSettings();
    rotary.init();
}

void loop() {
    updateRotary();
    displaySettings();
}

void updateRotary() {
    int pos = rotary.read() / 4; // Adjust the sensitivity
    if (pos != 0) {
        if (currentMenu == 'input') {
            currentInput = (currentInput + pos) % maxInputs;
        } else {
            // Adjust tone settings here
            toneSettings[currentTone] += pos;
        }
    }
}

void displaySettings() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Input: ");
    display.println(currentInput);
    // Example to show tone settings
    for (int i = 0; i < 5; i++) {
        display.print("Band ");
        display.print(i);
        display.print(": ");
        display.println(toneSettings[i]);
    }
    display.display();
}

void loadSettings() {
    EEPROM.get(0, toneSettings);
    // Load current input if needed
}

void saveSettings() {
    EEPROM.put(0, toneSettings);
}