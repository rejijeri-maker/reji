#include <Arduino.h>

// Pin definitions
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3
#define LED1_PIN 4
#define LED2_PIN 5
#define LED3_PIN 6
#define LED4_PIN 7

int ledState = 0;

void setup() {
    // Initialize LED pins
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);

    // Initialize encoder pins
    pinMode(ENCODER_A_PIN, INPUT);
    pinMode(ENCODER_B_PIN, INPUT);
}

void loop() {
    int encoderA = digitalRead(ENCODER_A_PIN);
    int encoderB = digitalRead(ENCODER_B_PIN);

    if (encoderA == HIGH) {
        // Increment LED state
        ledState = (ledState + 1) % 4;
    } else if (encoderB == HIGH) {
        // Decrement LED state
        ledState = (ledState - 1 + 4) % 4;
    }

    // Control LEDs based on ledState
    digitalWrite(LED1_PIN, ledState == 0);
    digitalWrite(LED2_PIN, ledState == 1);
    digitalWrite(LED3_PIN, ledState == 2);
    digitalWrite(LED4_PIN, ledState == 3);

    delay(100); // Debouncing delay
}