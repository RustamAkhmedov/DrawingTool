#include "LineTool.h"
#include <iostream>

#include "Line.h"

using namespace std;

Shape* LineTool::createShape(int xStart, int yStart, int xEnd, int yEnd, Color color) {
    return new Line( xStart, yStart, xEnd, yEnd ,color);
}

void LineTool::drawPreview(int xStart, int yStart, int currX, int currY, Color color) {
    DrawLineEx({ static_cast<float>(xStart), static_cast<float>(yStart) },
                    { static_cast<float>(currX), static_cast<float>(currY) },
                    5.0f, color);
}