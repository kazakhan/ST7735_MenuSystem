/**
 * @file MenuItem.cpp
 * @brief Implementation of MenuItem class
 * @author Jamie Saunders
 * @date 2023
 * @copyright GNU LGPL-3.0 license
 */

#include "MenuItem.h"

MenuItem::MenuItem(String label, MenuItemType type)
    : label(label), type(type), value(0), step(0.1), minVal(0), maxVal(1) {}

MenuItem::MenuItem(String label, float val, float step, float minV, float maxV)
    : label(label), type(VALUE), value(val), step(step), minVal(minV), maxVal(maxV) {}

void MenuItem::adjust(bool up) {
    if (type == VALUE) {
        value += up ? step : -step;
        if (value > maxVal) value = maxVal;
        if (value < minVal) value = minVal;
    }
}

String MenuItem::getDisplayText() const {
    if (type == VALUE) return label + ": " + String(value, 2);
    return label;
}