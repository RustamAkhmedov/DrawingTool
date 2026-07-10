#include "TriangleTool.h"
#include <iostream>

#include "Triangle.h"

using namespace std;

Shape* TriangleTool::createShape(int xStart, int yStart, int xEnd, int yEnd, Color color) {
    int left   = std::min(xStart, xEnd);
    int right  = std::max(xStart, xEnd);
    int top    = std::min(yStart, yEnd);
    int bottom = std::max(yStart, yEnd);

    int x1 = (left + right) / 2;
    int y1 = top;

    int x2 = left;
    int y2 = bottom;

    int x3 = right;
    int y3 = bottom;

    return new Triangle(x1, y1, x2, y2, x3, y3, color);
}

void TriangleTool::drawPreview(int xStart, int yStart, int currX, int currY, Color color) {
    int left   = std::min(xStart, currX);
    int right  = std::max(xStart, currX);
    int top    = std::min(yStart, currY);
    int bottom = std::max(yStart, currY);

    float x1 = (left + right) / 2;
    float y1 = top;

    float x2 = left;
    float y2 = bottom;

    float x3 = right;
    float y3 = bottom;

    DrawTriangle({x1, y1}, {x2, y2}, {x3, y3}, color);
}