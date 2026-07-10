#include "Drawing.h"
#include <iostream>

#include "Circle.h"
#include "Line.h"
#include "Triangle.h"
#include "../tools/CircleTool.h"
#include "../tools/LineTool.h"
#include "../tools/RectTool.h"
#include "../tools/TriangleTool.h"

using namespace std;

void Drawing::copyArray( Shape **dst, Shape **src, int noe) {
    for (int i = 0; i < noe; i++) {
        dst[i] = src[i];
    }
}

void Drawing::deleteArray( Shape **arr, int noe) {
    for (int i = 0; i<noe; i++) {
        delete arr[i];
    }
}

Drawing::Drawing() : shapes(nullptr), noe(0), currentType(0), selectMode(false) {
    types[0] = new RectTool();
    types[1] = new CircleTool();
    types[2] = new LineTool();
    types[3] = new TriangleTool();
}

Drawing::Drawing(const Drawing &d) {
    this->shapes = new Shape *[d.noe];
    copyArray(this->shapes, d.shapes, d.noe);
    this->noe = d.noe;
}

Drawing &Drawing::operator=(const Drawing &d) {
    if (this != &d) {
        deleteArray(shapes, noe);
        delete[] shapes;

        this->shapes = new Shape *[d.noe];
        copyArray(this->shapes, d.shapes, d.noe);
        this->noe = d.noe;
    }
    return *this;
}

Drawing::~Drawing() {
   delete[] shapes;
}

void Drawing::add(Shape* r) {
    Shape ** newShapes = new Shape*[noe+1];
    copyArray(newShapes, shapes, noe);
    newShapes[noe] = r;
    noe++;
    delete[] shapes;
    shapes = newShapes;
}

void Drawing::draw() {
    for (int i = 0; i < noe; i++) {
        shapes[i]->draw();
    }
}

void Drawing::undo() {
    if (noe >= 1) {
        noe--;
        Shape ** newShapes = new Shape*[noe];
        copyArray(newShapes, shapes, noe);
        delete[] shapes;
        shapes = newShapes;
    }
}

void Drawing::clear() {
    deleteArray(shapes, noe);
    this->noe = 0;
    delete[] shapes;
    shapes = NULL;
}

void Drawing::changeColor(Color color) {
    this->color = color;
    for (int i = 0; i<noe; i++) {
        if (shapes[i]->isSelected()) shapes[i]->setColor(color);
    }
}

Color Drawing::getColor() {
    return this->color;
}

void Drawing::setType(int type) {
    this->currentType = type;
}

DrawingTool *Drawing::getCurrentType() {
    return types[currentType];
}

void Drawing::select() {
    int index = -1;
    int i;
    if (this->getSelectMode()) {
        for (i = 0; i<noe; i++) {
            if (shapes[i]->contains(GetMouseX(), GetMouseY())) {
                index = i;
                shapes[i]->setSelected(true);
                break;
            }
        }
    }

    if (i != noe) {
        for (int j = 0; j<noe; j++) {
            if (j != index) shapes[j]->setSelected(false);
        }
    }
}

void Drawing::move(const Line& l) {
    int dx = l.getDX();
    int dy = l.getDY();
    Shape* shape = getSelected();
    if (shape) shape->move(dx, dy);
}

bool Drawing::drag(int mx, int my) {
    for (int i = 0; i<noe; i++) {
        if (shapes[i]->contains(mx,my) && shapes[i]->isSelected()) return true;
    }
    return false;
}

void Drawing::deleteSelected() {
    int indx = getSelectedIndx();
    if (indx >= 0) {
        noe--;
        for (int i = indx; i < noe; i++) {
            shapes[i] = shapes[i+1];
        }
        Shape ** newShapes = new Shape*[noe];
        copyArray(newShapes, shapes, noe);
        delete[] shapes;
        shapes = newShapes;
    }
}

Shape *Drawing::getSelected() {
    for (int i = 0; i<noe; i++) {
        if (shapes[i]->isSelected()) {
            return shapes[i];
        }
    }
    return nullptr;
}

int Drawing::getSelectedIndx() {
    int indx = -1;
    for (int i = 0; i<noe; i++) {
        if (shapes[i]->isSelected()) {
            indx = i;
        }
    }
    return indx;
}

void Drawing::setSelectMode(bool s) {
    this->selectMode = s;
}

bool Drawing::getSelectMode() {
    return this->selectMode;
}


void Drawing::save() {
    FILE* f = fopen("drawing.txt", "wb");
    if (!f) return;

    fwrite(&noe, sizeof(int), 1, f);

    for (int i = 0; i < noe; ++i) {
        shapes[i]->save(f);
    }

    fclose(f);
    saved = true;
}

void Drawing::load() {
    FILE* f = fopen("drawing.txt", "rb");
    if (!f) return;

    this->clear();
    int fakeNoe;
    fread(&fakeNoe, sizeof(int), 1, f);

    for (int i = 0; i < fakeNoe; ++i) {
        if (Shape* s = loadShape(f)) {
            this->add(s);
        }
    }
    noe = fakeNoe;

    for (int i = 0; i<noe; i++) {
        cout << shapes[i]->getX() << "X Cords" << endl;
    }

    fclose(f);
}

Shape* Drawing::loadShape(FILE* f) {
    ShapeType t;
    if (fread(&t, sizeof(ShapeType), 1, f) != 1) return nullptr;

    cout << "LOAD TYPE" << static_cast<int>(t) << endl << "!!!!!!!!!!!!" << endl;
    switch (t) {
        case ShapeType::Rectangle: {
            int x, y, width, height;
            Color c;
            fread(&x, sizeof(int), 1, f);
            fread(&y, sizeof(int), 1, f);
            fread(&width, sizeof(int), 1, f);
            fread(&height, sizeof(int), 1, f);
            fread(&c, sizeof(Color), 1, f);
            return new MyRectangle(x, y, width, height, c);
        }
        case ShapeType::Circle: {
            int x, y, r;
            Color c;
            fread(&x, sizeof(int), 1, f);
            fread(&y, sizeof(int), 1, f);
            fread(&r, sizeof(int), 1, f);
            fread(&c, sizeof(Color), 1, f);
            return new Circle(x, y, r, c);
        }
        case ShapeType::Line: {
            int x, y, x2, y2;
            Color c;
            fread(&x, sizeof(int), 1, f);
            fread(&y, sizeof(int), 1, f);
            fread(&x2, sizeof(int), 1, f);
            fread(&y2, sizeof(int), 1, f);
            fread(&c, sizeof(Color), 1, f);
            return new Line(x, y, x2, y2, c);
        }
        case ShapeType::Triangle: {
            int x, y, x1, y1, x2, y2;
            Color c;
            fread(&x, sizeof(int), 1, f);
            fread(&y, sizeof(int), 1, f);
            fread(&x1, sizeof(int), 1, f);
            fread(&y1, sizeof(int), 1, f);
            fread(&x2, sizeof(int), 1, f);
            fread(&y2, sizeof(int), 1, f);
            fread(&c, sizeof(Color), 1, f);
            return new Triangle(x, y, x1, y1, x2, y2, c);
        }
        default: {
            return nullptr;
        }

    }
}

bool Drawing::getSaved() {
    return this->saved;
}
