#include "MyRectangle.h"

#include <cstdio>
#include <iostream>

#include "raylib.h"

MyRectangle::MyRectangle(int x, int y, int width, int height, Color color)
    : Shape(x,y,color), width(width), height(height) {
}

int MyRectangle::getX() const {
    return x;
}

int MyRectangle::getY() const {
    return y;
}

int MyRectangle::getWidth() const {
    return width;
}

int MyRectangle::getHeight() const {
    return height;
}

void MyRectangle::setX(int x) {
    this->x = x;
}

void MyRectangle::setY(int y) {
    this->y = y;
}

void MyRectangle::setWidth(int width) {
    this->width = width;
}

void MyRectangle::setHeight(int height) {
    this->height = height;
}

void MyRectangle::setColor(Color color) {
    this->color = color;
}

void MyRectangle::draw() const {
    DrawRectangle(x, y, width, height, color);
    drawOutline();
}

Shape *MyRectangle::clone() {
    return new MyRectangle(*this);
}

bool MyRectangle::contains(int mouseX, int mouseY) {
    return ( mouseX >= x && mouseX <= x + getWidth() &&
             mouseY >= y && mouseY <= y + getHeight());
}

void MyRectangle::move(int dx, int dy) {
    this->x += dx;
    this->y += dy;
}

void MyRectangle::save(FILE* f) const {

    ShapeType t = ShapeType::Rectangle;

    fwrite(&t, sizeof(ShapeType), 1, f);
    fwrite(&x, sizeof(int), 1, f);
    fwrite(&y, sizeof(int), 1, f);
    fwrite(&width, sizeof(int), 1, f);
    fwrite(&height, sizeof(int), 1, f);
    fwrite(&color, sizeof(Color), 1, f);
}

void MyRectangle::drawOutline() const {
    if (selected) {
        DrawRectangleLinesEx(Rectangle{static_cast<float>( x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height) }, 3.0f, BLACK);
    }
}
