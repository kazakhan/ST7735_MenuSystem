/**
 * @file MenuSystem.cpp
 * @brief Implementation of MenuSystem class
 * @author Jamie Saunders
 * @date 2023
 * @copyright GNU LGPL-3.0 license
 */

#include "MenuSystem.h"

MenuSystem::MenuSystem(Adafruit_ST7735* tft) : tft(tft) {
    // Create a 128x128 offscreen canvas buffer
    canvas = new GFXcanvas16(128, 128);
}

MenuSystem::~MenuSystem() {
    delete canvas;
}

void MenuSystem::setPage(MenuPage* page) {
    currentPage = page;
    selectedIndex = 0;
    editing = false;
    draw();
}

void MenuSystem::encoderMove(bool clockwise) {
    uint8_t oldIndex = selectedIndex;
    if (!editing) {
        if (clockwise) {
            selectedIndex++;
            if (selectedIndex >= currentPage->size()) selectedIndex = 0;
        } else {
            if (selectedIndex == 0) selectedIndex = currentPage->size() - 1;
            else selectedIndex--;
        }
    } else {
        currentPage->getItem(selectedIndex)->adjust(clockwise);
    }
    draw();
}

void MenuSystem::encoderButton() {
    MenuItem* item = currentPage->getItem(selectedIndex);
    if (item->type == VALUE) {
        editing = !editing;
    } else if (item->type == SUBMENU) {
        setPage(item->linkedPage);
    } else if (item->type == ACTION && item->onSelect) {
        item->onSelect();
    }
    draw();
}

void MenuSystem::draw() {
    // Clear the canvas
    canvas->fillScreen(ST7735_WHITE);
    // Draw title
    canvas->setTextColor(ST7735_BLACK);
    canvas->setTextSize(1);
    canvas->setCursor(2, 2);
    canvas->println(currentPage->title);
    // Draw all menu items
    for (uint8_t i = 0; i < currentPage->size(); i++) {
        MenuItem* item = currentPage->getItem(i);
        uint16_t y = ITEM_Y_OFFSET + i * ITEM_HEIGHT;
        // Highlight the selected item
        uint16_t bgColor = (i == selectedIndex) ? ST7735_BLUE : ST7735_WHITE;
        uint16_t fgColor = (i == selectedIndex) ? ST7735_WHITE : ST7735_BLACK;
        canvas->fillRect(2, y, 124, ITEM_HEIGHT - 2, bgColor);
        canvas->setCursor(6, y + 2);
        canvas->setTextColor(fgColor);
        canvas->print(item->getDisplayText());
    }
    // Push the entire buffer to the display in one call
    tft->drawRGBBitmap(0, 0, (uint16_t*)canvas->getBuffer(), 128, 128);
}