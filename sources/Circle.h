#pragma once
#include "Shape.h"

class Circle : public Shape{
private:
    int radius;
public:
    Circle(int x, int y, int r, Color c);

    virtual void draw() const;
    virtual bool contains(int mouseX, int mouseY);
    virtual Shape* clone();
    virtual void move(int dx, int dy) override;
    ShapeType getType() const override { return ShapeType::Circle; }
    virtual void save(FILE* f) const override;
    virtual void drawOutline() const;
};