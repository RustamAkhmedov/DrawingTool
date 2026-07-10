#pragma once
#include "Shape.h"

class Triangle : public Shape{
private:
    int x1;
    int y1;
    int x2;
    int y2;
public:
    Triangle(int x, int y, int x1, int y1, int x2, int y2, Color color);

    virtual void draw() const;
    virtual bool contains(int mouseX, int mouseY);
    virtual Shape* clone();
    virtual void move(int dx, int dy) override;
    virtual ShapeType getType() const { return ShapeType::Triangle; }
    virtual void save(FILE* f) const override;
    virtual void drawOutline() const;


};