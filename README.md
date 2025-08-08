# ST7735 Menu System Library

![Menu System Demo](/ST7735_Menu.jpg) 

A hierarchical menu system for ST7735 displays with rotary encoder navigation. Perfect for Arduino projects needing a user interface.

## Features

- **Three Menu Item Types**:
  - **Action Items**: Trigger callback functions
  - **Value Items**: Editable numeric values with min/max limits
  - **Submenu Items**: Navigate to nested menus
- **Smooth Display Updates**: Uses GFXcanvas16 for flicker-free rendering
- **Rotary Encoder Support**: Built-in handling for navigation
- **Customizable Appearance**: Easy to modify colors and layout

## Installation

1. **Install Dependencies**:
   - [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
   - [Adafruit ST7735 Library](https://github.com/adafruit/Adafruit-ST7735-Library)
   - [RotaryEncoder Library](https://github.com/kazakhan/RotaryEncoder) [Used in the example, not required]

2. **Install the Menu Library**:
   - Download the latest release ZIP
   - In Arduino IDE: Sketch → Include Library → Add .ZIP Library...

## Basic Usage

```cpp
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

	// Add Settings page
    MenuItem* settingsItem = new MenuItem("Settings", SUBMENU);
    settingsItem->linkedPage = &settings;
    mainMenu.add(settingsItem);

    // Add items to settings menu
    settings.add(new MenuItem("Voltage", 3.0, 0.1, 0, 25));
    settings.add(new MenuItem("Current", 1.0, 0.1, 0, 5));

    MenuItem* backItem = new MenuItem("Back", SUBMENU);
    backItem->linkedPage = &mainMenu;

    settings.add(backItem);

