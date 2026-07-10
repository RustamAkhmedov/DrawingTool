#include "Circle.h"
#include <iostream>

#include "raylib.h"
#include "Shape.h"

using namespace std;

Circle::Circle(int x, int y, int r, Color c)
    : Shape(x,y,c), radius(r){}

Shape *Circle::clone() {
    return new Circle(*this);
}

bool Circle::contains(int mouseX, int mouseY) {
    return CheckCollisionPointCircle(
        {static_cast<float>(mouseX), static_cast<float>(mouseY)},
    {static_cast<float>(x), static_cast<float>(y)}, radius);
}

void Circle::draw() const {
    DrawCircle(x, y, radius, color);
    drawOutline();
}

void Circle::move(int dx, int dy) {
    this->x += dx;
    this->y += dy;
}

void Circle::save(FILE* f) const {

    ShapeType t = ShapeType::Circle;
    fwrite(&t, sizeof(ShapeType), 1, f);
    fwrite(&x, sizeof(int), 1, f);
    fwrite(&y, sizeof(int), 1, f);
    fwrite(&radius, sizeof(int), 1, f);
    fwrite(&color, sizeof(Color), 1, f);
}

void Circle::drawOutline() const {
    if ( selected) {
        for (int i = 1; i < 3; i++) {
            DrawCircleLines(x, y, radius - i, BLACK);
            DrawCircleLines(x, y, radius + i, BLACK);
        }
    }
}
