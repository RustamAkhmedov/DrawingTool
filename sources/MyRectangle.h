#pragma once
#include "raylib.h"
#include "Shape.h"


class MyRectangle : public Shape{
private:
    int width;
    int height;

public:
    MyRectangle(int x = 0, int y = 0, int width = 0, int height = 0, Color color = { 255, 109, 194, 255 });
    
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    void setColor(Color color);

    virtual bool contains(int mouseX, int mouseY);
    virtual Shape* clone();
    virtual void move(int dx, int dy) override;
    ShapeType getType() const override { return ShapeType::Rectangle; }
    virtual void save(FILE* f) const override;
    virtual void drawOutline() const;



    void draw() const;
};
