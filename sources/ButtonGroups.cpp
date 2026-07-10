#include "ButtonGroups.h"
#include <iostream>

using namespace std;

ButtonGroups::ButtonGroups(Button **array, int noe): noe(noe), buttons(array) {
}

void ButtonGroups::checkShortcuts() {
    int index = -1;
    int i;
    for (i = 0; i<noe; i++) {
        if (buttons[i]->shortCut()) {
            buttons[i]->setActive(true);
            index = i;
            break;
        }
    }
    if (noe != i) {
        for (int j = 0; j<noe; j++) {
            if (j != index) buttons[j]->setActive(false);
        }
    }
}

void ButtonGroups::clickSelect() {
    int index = -1;
    int i;
    for (i = 0; i<noe; i++) {
        if (buttons[i]->click()) {
            buttons[i]->setActive(true);
            index = i;
            break;
        }
    }
    if ( noe != i) {
        for (int j = 0; j<noe; j++) {
            if (j != index) buttons[j]->setActive(false);
        }
    }
}

void ButtonGroups::draw() {
    for (int i = 0; i<noe; i++) {
        buttons[i]->draw();
    }
}
