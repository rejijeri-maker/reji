# ATmega328P Audio Selector with OLED Display

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define NUM_OPTIONS 5
const char *options[NUM_OPTIONS] = {"LINE-IN", "CD", "TUNER", "AUX", "DAC"};

// Pin definitions
#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_4 5
#define LED_PIN_5 6
#define ENCODER_A 8
#define ENCODER_B 9

volatile int ledIndex = 0;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
    pinMode(LED_PIN_3, OUTPUT);
    pinMode(LED_PIN_4, OUTPUT);
    pinMode(LED_PIN_5, OUTPUT);
    // Setup encoder
    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), updateLedIndex, CHANGE);
    
    display.begin(SSD1306_I2C_ADDRESS, 0x3C);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
}

void loop() {
    display.clearDisplay();
    animation();
    display.setCursor(0, 0);
    display.println(options[ledIndex]);
    display.display();
    delay(200);
}

void updateLedIndex() {
    if (digitalRead(ENCODER_A) == digitalRead(ENCODER_B)) {
        ledIndex = (ledIndex + 1) % NUM_OPTIONS;
    } else {
        ledIndex = (ledIndex - 1 + NUM_OPTIONS) % NUM_OPTIONS;
    }
    updateLEDs();
}

void updateLEDs() {
    digitalWrite(LED_PIN_1, ledIndex == 0);
    digitalWrite(LED_PIN_2, ledIndex == 1);
    digitalWrite(LED_PIN_3, ledIndex == 2);
    digitalWrite(LED_PIN_4, ledIndex == 3);
    digitalWrite(LED_PIN_5, ledIndex == 4);
}

void animation() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN_1 + i, HIGH);
        delay(100);
        digitalWrite(LED_PIN_1 + i, LOW);
    }
}