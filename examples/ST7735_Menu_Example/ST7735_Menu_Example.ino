#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <MenuItem.h>
#include <MenuPage.h>
#include <MenuSystem.h>

#include <RotaryEncoder.h>

// Pins
#define ENC_A 22
#define ENC_B 19
#define ENC_BTN 21

RotaryEncoder enc(ENC_A, ENC_B, ENC_BTN);

  #define TFT_CS         15
  #define TFT_RST        2 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         4

#define TFT_MOSI 23  // Data out
#define TFT_SCLK 18  // Clock out

// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

MenuSystem* menu;

MenuPage mainMenu("Main Menu");
MenuPage settings("Settings");

void setup() {
    tft.initR(INITR_BLACKTAB);
    tft.setSPISpeed(27000000); // 27 MHz for faster updates
    tft.fillScreen(ST7735_WHITE);

    enc.begin();

    // Add items to main menu
    MenuItem* startItem = new MenuItem("Start", ACTION);
    startItem->onSelect = []() {
        Serial.println("Start button pressed!");
        // put your actual start code here
    };
    mainMenu.add(startItem);
    MenuItem* stopItem = new MenuItem("Stop", ACTION);
    startItem->onSelect = []() {
        Serial.println("Stop button pressed!");
        // put your actual start code here
    };
    mainMenu.add(stopItem);

    MenuItem* settingsItem = new MenuItem("Settings", SUBMENU);
    settingsItem->linkedPage = &settings;
    mainMenu.add(settingsItem);

    // Add items to settings menu
    settings.add(new MenuItem("Voltage", 3.0, 0.1, 0, 25));
    settings.add(new MenuItem("Current", 1.0, 0.1, 0, 5));

    MenuItem* backItem = new MenuItem("Back", SUBMENU);
    backItem->linkedPage = &mainMenu;
    settings.add(backItem);

    menu = new MenuSystem(&tft);
    menu->setPage(&mainMenu);
}

void loop() {
    int8_t currentDirection;
    if (enc.getDirection(currentDirection)) {
        // Only enters here when fresh movement exists
        if (currentDirection == 1) {
            menu->encoderMove(true);
        } 
        else if (currentDirection == -1) {
            menu->encoderMove(false);// Handle counter-clockwise turn  
        }
    }
    if (enc.getButtonPress()) {
        menu->encoderButton();
    }  
}
