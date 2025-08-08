/**
 * @file MenuItem.h
 * @brief Menu item class definition
 * @author Jamie Saunders
 * @date 2023
 * @copyright GNU LGPL-3.0 license
 * 
 * Defines individual menu items that can be actions, editable values, or submenu links.
 */

#ifndef MenuItem_h
#define MenuItem_h

#include <Arduino.h>
#include <functional>

enum MenuItemType {
    ACTION,     // Triggers a callback
    VALUE,      // Adjustable number
    SUBMENU     // Opens another MenuPage
};

class MenuPage; // Forward declaration

class MenuItem {
public:
    String label;
    MenuItemType type;
    float value;
    float step;
    float minVal, maxVal;
    std::function<void()> onSelect;         // For ACTION
    MenuPage* linkedPage = nullptr;         // For SUBMENU

    MenuItem(String label, MenuItemType type);
    MenuItem(String label, float val, float step, float minV, float maxV);
    
    void adjust(bool up);
    String getDisplayText() const;
};

#endif