#include "Triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(int x, int y, int x1, int y1, int x2, int y2, Color color)
    : Shape(x,y,color), x1(x1), x2(x2), y1(y1), y2(y2) {}

Shape *Triangle::clone() {
    return new Triangle(*this);
}

bool Triangle::contains(int mouseX, int mouseY) {
    return CheckCollisionPointTriangle(
        {static_cast<float>(mouseX), static_cast<float>(mouseY)},
    {static_cast<float>(x), static_cast<float>(y)},
    {static_cast<float>(x1), static_cast<float>(y1)},
    {static_cast<float>(x2), static_cast<float>(y2)}
    );
}

void Triangle::draw() const {
    DrawTriangle({static_cast<float>(x), static_cast<float>(y)},
    {static_cast<float>(x1), static_cast<float>(y1)},
    {static_cast<float>(x2), static_cast<float>(y2)}, color);
    drawOutline();
}

void Triangle::move(int dx, int dy) {
    this->x += dx;
    this->y += dy;

    this->x1 += dx;
    this->y1 += dy;

    this->x2 += dx;
    this->y2 += dy;
}

void Triangle::save(FILE* f) const {
    ShapeType t = ShapeType::Triangle;
    fwrite(&t, sizeof(ShapeType), 1, f);
    fwrite(&x, sizeof(int), 1, f);
    fwrite(&y, sizeof(int), 1, f);
    fwrite(&x1, sizeof(int), 1, f);
    fwrite(&y1, sizeof(int), 1, f);
    fwrite(&x2, sizeof(int), 1, f);
    fwrite(&y2, sizeof(int), 1, f);
    fwrite(&color, sizeof(Color), 1, f);
}

void Triangle::drawOutline() const {
    if (selected) {
        Vector2 a = { static_cast<float>(x), static_cast<float>(y) };
        Vector2 b = { static_cast<float>(x1), static_cast<float>(y1) };
        Vector2 c = { static_cast<float>(x2), static_cast<float>(y2) };
        DrawLineEx(a, b, 3, color);
        DrawLineEx(b, c, 3, color);
        DrawLineEx(c, a, 3, color);
    }
}

