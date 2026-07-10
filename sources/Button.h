#pragma once
#include <cmath>

#include "raylib.h"
#include <string>
#include <functional>

#include "Drawing.h"
#include "MyRectangle.h"

using namespace std;

class Button : public MyRectangle{
private:
    bool active;
    string text;
    std::function<void()> function;

    int key;

    Color LightenColor(Color c, float factor);
public:
    Button(std::function<void()> func, int x = 0, int y = 0, int width = 0, int height = 0, const string& t = "", Color color = { 255, 109, 194, 255 }, int key = -1);

    void draw();
    bool click();
    bool shortCut();

    void setActive(bool active);
    bool getActive();
};
