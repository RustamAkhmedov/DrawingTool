#include <cstdio>
#include <cmath>
// #include "Drawing.h"
#include <iostream>

#include "Button.h"
#include "ButtonGroups.h"
#include "Drawing.h"
#include "LineTool.h"
#include "raylib.h"
#include "MyRectangle.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "First Exercise"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);
    MaximizeWindow();
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    printf("%d/%d", windowWidth, windowHeight);

    // coordinates for colors
    float buttonX = SCREEN_WIDTH * 3.3;  // idk why Screen width = screenwidth * 3,5 or smth
    float buttonWidth = 200;
    float buttonHeight = 80;
    float spacing = 100;

    Drawing drawing;

    // Draw / Select Group
    Button draw(std::bind(&Drawing::setSelectMode, &drawing, false), SCREEN_WIDTH*0.05,  SCREEN_HEIGHT*0.10, 200, 80, "Draw", GRAY, KEY_D);
    Button select(std::bind(&Drawing::setSelectMode, &drawing, true), SCREEN_WIDTH*0.05 + 220,  SCREEN_HEIGHT*0.10, 200, 80, "Select", GRAY, KEY_S);
    Button **drawSelectArray = new Button *[2] {&draw, & select};
    ButtonGroups drawSelect(drawSelectArray, 2);

    // functions
    Button undo(std::bind(&Drawing::undo, &drawing), SCREEN_WIDTH*0.05 + 480,  SCREEN_HEIGHT*0.10, 200, 80, "Undo", GRAY, KEY_U);
    Button clear(std::bind(&Drawing::clear, &drawing), SCREEN_WIDTH*0.05 + 700,  SCREEN_HEIGHT*0.10, 200, 80, "Clear", GRAY, KEY_C);
    Button deleteSelected(std::bind(&Drawing::deleteSelected, &drawing), SCREEN_WIDTH*0.05 + 920,  SCREEN_HEIGHT*0.10, 200, 80, "Delete", GRAY, KEY_DELETE);
    Button **functionsArray = new Button *[3] {&undo, &clear, &deleteSelected};
    ButtonGroups functions(functionsArray, 3);

    // saving / loading
    Button save(std::bind(&Drawing::save, &drawing), SCREEN_WIDTH*0.05 + 1140,  SCREEN_HEIGHT*0.10, 200, 80, "Save", GRAY);
    Button load (std::bind(&Drawing::load, &drawing), SCREEN_WIDTH*0.05 + 1360,  SCREEN_HEIGHT*0.10, 200, 80, "Load", GRAY);
    Button **saveLoadArray = new Button *[2] {&save, &load};
    ButtonGroups saveLoad(saveLoadArray, 2);

    // tools
    Button rect(std::bind(&Drawing::setType, &drawing, 0), SCREEN_WIDTH*0.05,  SCREEN_HEIGHT*0.35, 200, 80, "Rect", GRAY, KEY_ONE);
    Button circle(std::bind(&Drawing::setType, &drawing, 1), SCREEN_WIDTH*0.05 + 220,  SCREEN_HEIGHT*0.35, 200, 80, "Circle", GRAY, KEY_TWO);
    Button line(std::bind(&Drawing::setType, &drawing, 2), SCREEN_WIDTH*0.05 + 440,  SCREEN_HEIGHT*0.35, 200, 80, "Line", GRAY, KEY_THREE);
    Button triangle(std::bind(&Drawing::setType, &drawing, 3), SCREEN_WIDTH*0.05 + 660,  SCREEN_HEIGHT*0.35, 200, 80, "Triangle", GRAY, KEY_FOUR);
    Button **toolsArray = new Button *[4] {&rect, &circle, &line, &triangle};
    ButtonGroups tools(toolsArray, 4);

    // colors
    Button colorDarkGray(std::bind(&Drawing::changeColor, &drawing, DARKGRAY), buttonX, spacing * 0, buttonWidth, buttonHeight, "Dark Gray", DARKGRAY);
    Button colorRed     (std::bind(&Drawing::changeColor, &drawing, RED),      buttonX, spacing * 1, buttonWidth, buttonHeight, "Red", RED);
    Button colorOrange  (std::bind(&Drawing::changeColor, &drawing, ORANGE),   buttonX, spacing * 2, buttonWidth, buttonHeight, "Orange", ORANGE);
    Button colorYellow  (std::bind(&Drawing::changeColor, &drawing, YELLOW),   buttonX, spacing * 3, buttonWidth, buttonHeight, "Yellow", YELLOW);
    Button colorGreen   (std::bind(&Drawing::changeColor, &drawing, GREEN),    buttonX, spacing * 4, buttonWidth, buttonHeight, "Green", GREEN);
    Button colorBlue    (std::bind(&Drawing::changeColor, &drawing, BLUE),     buttonX, spacing * 5, buttonWidth, buttonHeight, "Blue", BLUE);
    Button colorPurple  (std::bind(&Drawing::changeColor, &drawing, PURPLE),   buttonX, spacing * 6, buttonWidth, buttonHeight, "Purple", PURPLE);
    Button colorGray    (std::bind(&Drawing::changeColor, &drawing, GRAY),     buttonX, spacing * 7, buttonWidth, buttonHeight, "Gray", GRAY);
    Button **colorArray = new Button *[8] {&colorRed, &colorGreen, &colorBlue, &colorDarkGray,
                                        &colorPurple, &colorOrange, &colorYellow, &colorGray};
    ButtonGroups colors(colorArray, 8);


    int xStart = -1, yStart = -1;

    // TODO: Known bugs: move moves even outside of object
    // TODO: Style Class for selected Onjects
    // TODO: Shortcuts mit einer Variable in button, und neuer Funktion dazu.
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (drawing.getSaved()) DrawText("Saved to 'drawing.txt'", 20, SCREEN_HEIGHT * 3, 20, DARKBLUE);
        DrawText("Shortcuts: 1-4 Tools, D draw, S select, del delete", 20, SCREEN_HEIGHT * 3 + 100, 20, BLACK);

        // drawing buttons
        drawSelect.draw();
        functions.draw();
        saveLoad.draw();
        if (drawing.getSelectMode() == false) {
            tools.draw();
        }
        colors.draw();

        // shortcuts
        if (IsKeyPressed(KEY_F)) ToggleFullscreen();
        drawSelect.checkShortcuts();
        if (drawing.getSelectMode() == false) {
            tools.checkShortcuts();
        }
        deleteSelected.shortCut();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            xStart = GetMouseX();
            yStart = GetMouseY();
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            int xEnd = GetMouseX();
            int yEnd = GetMouseY();
            if (yStart != yEnd && xStart != xEnd) {
                // moving selected form
                if (drawing.getSelectMode()) {
                    drawing.move(Line(xStart, yStart, xEnd, yEnd, GRAY));
                } else {
                    Shape* s = drawing.getCurrentType()->createShape(xStart, yStart, xEnd, yEnd, drawing.getColor());
                    drawing.add(s);
                }
            } else {
                // Check for all Clicks, must be click
                drawSelect.clickSelect();

                // is no select
                clear.click();
                undo.click();
                deleteSelected.click();
                save.click();
                load.click();

                if (drawing.getSelectMode() == false) {
                    tools.clickSelect();
                }
                drawing.select();
                colors.clickSelect();
            }

            xStart = -1;
            yStart = -1;
        }
        if (drawing.getSelectMode() == false && xStart >= 0 && yStart >= 0) {
            drawing.getCurrentType()->drawPreview(xStart, yStart, GetMouseX(), GetMouseY(), drawing.getColor());
        }
        drawing.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
