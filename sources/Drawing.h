#pragma once
#include "Line.h"
#include "MyRectangle.h"
#include "raylib.h"
#include "../tools/DrawingTool.h"


class Drawing {
private:
    int noe;
    Shape **shapes;

    void deleteArray( Shape **arr, int noe);
    void copyArray( Shape **dst, Shape **src, int noe);
    Color color = PINK ;

    int currentType;
    DrawingTool *types[4];

    bool selectMode;

    Shape* getSelected();
    int getSelectedIndx();
    Shape* loadShape(FILE* f);

    bool saved = false;
public:
    Drawing();
    Drawing(const Drawing& d);
    Drawing &operator=(const Drawing& d);
    ~Drawing();

    void add(Shape* r);
    void draw();

    void undo();
    void clear();
    void deleteSelected();
    void changeColor(Color color);

    Color getColor();

    void setType(int type);
    DrawingTool* getCurrentType();

    void select();
    void move(const Line& l);
    bool drag(int mx, int my);

    void setSelectMode(bool s);
    bool getSelectMode();

    void save();
    void load();

    bool getSaved();
};
