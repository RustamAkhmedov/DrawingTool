#pragma once
#include "Button.h"

class ButtonGroups {
private:
    Button **buttons;
    int noe;
public:
    ButtonGroups(Button **array, int noe);

    void checkShortcuts();
    void clickSelect();

    void draw();
};
