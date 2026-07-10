#pragma once
#include <cstdio>

#include "raylib.h"
#include "ShapeType.h"


class Shape {

protected:
    int x;
    int y;
    Color color;
    bool selected;

public:
    Shape(int x = 0, int y = 0, Color color = GRAY, bool selected = false);

    virtual void draw() const = 0;
    virtual bool contains(int mouseX, int mouseY) = 0;
    virtual Shape* clone() = 0;
    virtual ~Shape() = default;
    virtual void move(int dx, int dy) = 0;
    virtual ShapeType getType() const = 0;
    virtual void save(FILE* f) const = 0;
    virtual void drawOutline() const = 0;

    bool isSelected();
    void setSelected(bool selected);
    Color getColor();
    void setColor(Color color);
    int getX() { return x;}
};
