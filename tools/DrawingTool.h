#pragma once
#include "Shape.h"

class DrawingTool{
private:

public:
    virtual ~DrawingTool() = default;
    virtual Shape* createShape(int xStart, int yStart, int xEnd, int yEnd, Color color) = 0;
    virtual void drawPreview(int xStart, int yStart, int currX, int currY, Color color) = 0;
};
