#pragma once
#include "Shape.h"

class Line : public Shape{
private:
    int endX;
    int endY;
    const int width = 20;
public:
    Line(int x, int y, int endX, int endY, Color color);

    virtual void draw() const;
    virtual bool contains(int mouseX, int mouseY);
    virtual Shape* clone();
    virtual void move(int dx, int dy) override;
    virtual ShapeType getType() const  { return ShapeType::Line; }
    virtual void save(FILE* f) const;
    virtual void drawOutline() const;

    int getDX() const;
    int getDY() const;
};