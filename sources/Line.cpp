#include "Line.h"
#include <iostream>

using namespace std;

Line::Line(int x, int y, int endX, int endY, Color color)
    : Shape(x,y,color), endX(endX), endY(endY) {}

Shape *Line::clone() {
    return new Line(*this);
}

bool Line::contains(int mouseX, int mouseY) {
    return CheckCollisionPointLine(
        {static_cast<float>(mouseX), static_cast<float>(mouseY)},
        {static_cast<float>(x), static_cast<float>(y)},
        {static_cast<float>(endX), static_cast<float>(endY)}, 8);
}

void Line::draw() const {
    DrawLineEx({ static_cast<float>(x), static_cast<float>(y) },
                { static_cast<float>(endX), static_cast<float>(endY) },
                5.0f, color);
    drawOutline();
}

int Line::getDX() const{
    return endX - x;
}

int Line::getDY() const{
    return endY - y;
}

void Line::move(int dx, int dy) {
    this->x += dx;
    this->y += dy;

    this->endX += dx;
    this->endY += dy;
}

void Line::save(FILE* f) const {

    ShapeType t = ShapeType::Line;
    fwrite(&t, sizeof(ShapeType), 1, f);
    fwrite(&x, sizeof(int), 1, f);
    fwrite(&y, sizeof(int), 1, f);
    fwrite(&endX, sizeof(int), 1, f);
    fwrite(&endY, sizeof(int), 1, f);
    fwrite(&color, sizeof(Color), 1, f);
}

void Line::drawOutline() const {
    if (selected) {
        DrawLineEx({ static_cast<float>(x), static_cast<float>(y) },
                { static_cast<float>(endX), static_cast<float>(endY)}, 5 + 3, BLACK);
        DrawLineEx({ static_cast<float>(x), static_cast<float>(y) },
                { static_cast<float>(endX), static_cast<float>(endY) },
                5.0f, color);
    }
}
