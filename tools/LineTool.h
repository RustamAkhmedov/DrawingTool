#pragma once
#include "DrawingTool.h"


class LineTool : public DrawingTool {
private:

public:
    Shape* createShape(int xStart, int yStart, int xEnd, int yEnd, Color color) override;
    void drawPreview(int xStart, int yStart, int currX, int currY, Color color) override;
    ~LineTool() override = default;
};
