#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// Cambodia average monthly temperature (°C)
int tempData[12] = {26, 28, 30, 31, 32, 31, 30, 30, 29, 28, 27, 26};
// Month labels
const char* months = "JFMAMJJASOND";

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED not found");
    while (1);
  }

  display.clearDisplay();

  // Draw Title
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 0);
  display.println("Cambodia Weather");

  // Graph area starts at y = 15
  int baseY = 60;   // Bottom of graph
  int barWidth = 8;

  for (int i = 0; i < 12; i++) {
    int barHeight = map(tempData[i], 25, 35, 2, 40);  
    int x = i * barWidth + 2;

    // Draw bar
    display.fillRect(x, baseY - barHeight, barWidth - 1, barHeight, SSD1306_WHITE);

    // Month letter
    display.setCursor(x + 1, baseY + 1);
    display.write(months[i]);
  }

  display.display();
}

void loop() { }
