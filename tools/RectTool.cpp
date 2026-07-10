#include "RectTool.h"
#include <iostream>

#include "MyRectangle.h"

using namespace std;

Shape* RectTool::createShape(int xStart, int yStart, int xEnd, int yEnd, Color color) {
    int rectX = (xStart < xEnd) ? xStart : xEnd;
    int rectY = (yStart < yEnd) ? yStart : yEnd;
    int rectWidth = abs(xEnd - xStart);
    int rectHeight = abs(yEnd - yStart);
    return new MyRectangle(rectX, rectY, rectWidth, rectHeight, color);
}

void RectTool::drawPreview(int xStart, int yStart, int currX, int currY, Color color) {
    int rectX = (xStart < currX) ? xStart : currX;
    int rectY = (yStart < currY) ? yStart : currY;
    int rectWidth = abs(currX - xStart);
    int rectHeight = abs(currY - yStart);
    DrawRectangle(rectX, rectY, rectWidth, rectHeight, color);
}