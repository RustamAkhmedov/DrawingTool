#include "Shape.h"
#include <iostream>

using namespace std;

Shape::Shape(int x, int y, Color color, bool selected)
    : x(x), y(y), color(color), selected(selected){
}

void Shape::setSelected(bool selected) {
    this->selected = selected;
}

void Shape::draw() const {

}

bool Shape::isSelected() {
    return selected;
}


Color Shape::getColor() {
    return this->color;
}

void Shape::setColor(Color color) {
    this->color = color;
}
