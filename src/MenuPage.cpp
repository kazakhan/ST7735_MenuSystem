/**
 * @file MenuPage.cpp
 * @brief Implementation of MenuPage class
 * @author Jamie Saunders
 * @date 2023
 * @copyright GNU LGPL-3.0 license
 */

#include "MenuPage.h"

MenuPage::MenuPage(String title) : title(title) {}

void MenuPage::add(MenuItem* item) {
    items.push_back(item);
}

MenuItem* MenuPage::getItem(uint8_t index) {
    if (index < items.size()) return items[index];
    return nullptr;
}

uint8_t MenuPage::size() const {
    return items.size();
}