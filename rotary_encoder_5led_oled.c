#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#include <EEPROM.h> 

#define OLED_ADDRESS 0x3C
#define BUTTON_PIN 2
#define ROTARY_A 3
#define ROTARY_B 4

// OLED display dimensions 
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int num_scenes = 5;
const char* scenes[num_scenes] = {"LINE-IN", "CD", "TUNER", "AUX", "DAC"};
int current_scene;
int last_scene;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ROTARY_A, INPUT);
  pinMode(ROTARY_B, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  current_scene = EEPROM.read(0);
  if(current_scene < 0 || current_scene >= num_scenes) {
    current_scene = 0;
  }
  last_scene = current_scene;
  displayScene(current_scene);
}

void loop() {
  static int last_A = HIGH;
  int A = digitalRead(ROTARY_A);
  if (A != last_A && A == LOW) {
    if (digitalRead(ROTARY_B) == HIGH) {
      current_scene--;
      if (current_scene < 0) current_scene = num_scenes - 1;
    } else {
      current_scene++;
      if (current_scene >= num_scenes) current_scene = 0;
    }
    displayScene(current_scene);
  }
  last_A = A;

  if (digitalRead(BUTTON_PIN) == LOW) {
    EEPROM.write(0, current_scene);
  }
}

void displayScene(int scene) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(scenes[scene]);
  display.display();
  delay(500); // Animation delay
}