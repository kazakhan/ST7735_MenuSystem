/**
 * @file MenuSystem.h
 * @brief Main menu system class for ST7735 displays
 * @author Jamie Saunders
 * @date 2023
 * @copyright GNU LGPL-3.0 license
 * 
 * Provides a hierarchical menu system with navigation using rotary encoders.
 * Uses Adafruit_ST7735 for display output and GFXcanvas16 for smooth updates.
 */

#ifndef MenuSystem_h
#define MenuSystem_h

#include <Adafruit_GFX.h>        // needed for GFXcanvas16
#include <Adafruit_ST7735.h>
#include "MenuPage.h"

#define ITEM_HEIGHT 16
#define ITEM_Y_OFFSET 18

class MenuSystem {
private:
    Adafruit_ST7735* tft;
    MenuPage* currentPage = nullptr;
    uint8_t selectedIndex = 0;
    bool editing = false;
    GFXcanvas16* canvas;

public:
    MenuSystem(Adafruit_ST7735* tft);
    ~MenuSystem();
    
    void setPage(MenuPage* page);
    void encoderMove(bool clockwise);
    void encoderButton();
    void draw();
};

#endif