#include "Button.h"
#include <iostream>
#include <utility>

using namespace std;

Button::Button(std::function<void()> func, int x, int y, int width, int height, const string &t, Color color, int key)
    : MyRectangle(x, y, width, height, color), text(t), function(func), active(false), key(key) {}

bool Button::click() {
    if (contains(GetMouseX(), GetMouseY())){
        function();
        return true;
    }
    return false;
}

void Button::draw() {
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), 20, 1);

    if (active) {
        DrawRectangle(this->getX(), this->getY(), this->getWidth(), this->getHeight(), LightenColor(getColor(), 0.4));
        DrawText(text.c_str(),
            getX() + (getWidth() - textSize.x) / 2,
            getY() + (getHeight() - textSize.y) / 2,
            20, WHITE);
        DrawRectangleLinesEx(Rectangle{static_cast<float>( this->getX()), static_cast<float>(this->getY()), 200, 80 }, 3.0f, BLACK);
    } else {
        DrawRectangle(this->getX(), this->getY(), this->getWidth(), this->getHeight(), getColor());
        DrawText(text.c_str(),
            getX() + (getWidth() - textSize.x) / 2,
            getY() + (getHeight() - textSize.y) / 2,
            20, WHITE);
    }
}

// idk some random copilot generated function
Color Button::LightenColor(Color c, float factor) {
    unsigned char r = (unsigned char)fminf(c.r + (255 - c.r) * factor, 255);
    unsigned char g = (unsigned char)fminf(c.g + (255 - c.g) * factor, 255);
    unsigned char b = (unsigned char)fminf(c.b + (255 - c.b) * factor, 255);
    return Color{ r, g, b, c.a };
}

bool Button::getActive() {
    return this->active;
}

void Button::setActive(bool active) {
    this->active = active;
}

bool Button::shortCut() {
    if (IsKeyPressed(key)) {
        function();
        return true;
    }
    return false;
}
