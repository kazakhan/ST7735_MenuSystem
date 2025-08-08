/**
 * @file MenuPage.h
 * @brief Menu page container class
 * @author Jamie Saunders
 * @date 2023
 * @copyright GNU LGPL-3.0 license
 * 
 * Represents a single page in the menu hierarchy containing multiple MenuItems.
 */

#ifndef MenuPage_h
#define MenuPage_h

#include <Arduino.h>
#include <vector>
#include "MenuItem.h"

class MenuPage {
public:
    String title;
    std::vector<MenuItem*> items;

    MenuPage(String title);
    void add(MenuItem* item);
    MenuItem* getItem(uint8_t index);
    uint8_t size() const;
};

#endif