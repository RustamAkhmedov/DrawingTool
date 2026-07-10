#include "CircleTool.h"

#include <cmath>
#include <iostream>

#include "Circle.h"

using namespace std;

Shape* CircleTool::createShape(int xStart, int yStart, int xEnd, int yEnd, Color color) {
    int radius = sqrt ((xEnd - xStart) * (xEnd - xStart)
                + (yEnd - yStart) * (yEnd - yStart));
    return new Circle(xStart, yStart, radius, color);
}

void CircleTool::drawPreview(int xStart, int yStart, int currX, int currY, Color color) {
    int radius = sqrt((currX - xStart) * (currX - xStart)
                + (currY - yStart) * (currY - yStart));
    DrawCircle(xStart, yStart, radius, color);
}