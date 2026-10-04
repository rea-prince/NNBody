/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    bool WindowBox000Active = true;
    bool Button006Pressed = false;
    bool ValueBOx006EditMode = false;
    int ValueBOx006Value = 0;
    bool ValueBOx007EditMode = false;
    int ValueBOx007Value = 0;
    bool TextBox008EditMode = false;
    char TextBox008Text[128] = "body name";
    bool ValueBOx012EditMode = false;
    int ValueBOx012Value = 0;
    bool ValueBOx013EditMode = false;
    int ValueBOx013Value = 0;
    bool ValueBOx014EditMode = false;
    int ValueBOx014Value = 0;
    bool ValueBOx015EditMode = false;
    int ValueBOx015Value = 0;
    bool ValueBOx016EditMode = false;
    int ValueBOx016Value = 0;
    bool ValueBOx017EditMode = false;
    int ValueBOx017Value = 0;
    bool ValueBOx018EditMode = false;
    int ValueBOx018Value = 0;
    bool ValueBOx019EditMode = false;
    int ValueBOx019Value = 0;
    bool ValueBOx020EditMode = false;
    int ValueBOx020Value = 0;
    bool DropdownBox022EditMode = false;
    int DropdownBox022Active = 0;
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            if (DropdownBox022EditMode) GuiLock();

            if (WindowBox000Active)
            {
                WindowBox000Active = !GuiWindowBox((Rectangle){ 0, 0, 296, 728 }, "SAMPLE TEXT");
            }
            GuiGroupBox((Rectangle){ 8, 112, 280, 608 }, "Bodies");
            GuiPanel((Rectangle){ 16, 120, 264, 144 }, NULL);
            Button006Pressed = GuiButton((Rectangle){ 184, 240, 80, 16 }, "remove");
            if (GuiValueBox((Rectangle){ 120, 240, 48, 16 }, "r", &ValueBOx006Value, 0, 100, ValueBOx006EditMode)) ValueBOx006EditMode = !ValueBOx006EditMode;
            if (GuiValueBox((Rectangle){ 56, 240, 48, 16 }, "m", &ValueBOx007Value, 0, 100, ValueBOx007EditMode)) ValueBOx007EditMode = !ValueBOx007EditMode;
            if (GuiTextBox((Rectangle){ 24, 128, 152, 24 }, TextBox008Text, 128, TextBox008EditMode)) TextBox008EditMode = !TextBox008EditMode;
            GuiLabel((Rectangle){ 24, 192, 24, 16 }, "v");
            GuiLabel((Rectangle){ 24, 216, 24, 16 }, "a");
            if (GuiValueBox((Rectangle){ 56, 192, 48, 16 }, "x", &ValueBOx012Value, 0, 100, ValueBOx012EditMode)) ValueBOx012EditMode = !ValueBOx012EditMode;
            if (GuiValueBox((Rectangle){ 120, 192, 48, 16 }, "y", &ValueBOx013Value, 0, 100, ValueBOx013EditMode)) ValueBOx013EditMode = !ValueBOx013EditMode;
            if (GuiValueBox((Rectangle){ 184, 192, 48, 16 }, "z", &ValueBOx014Value, 0, 100, ValueBOx014EditMode)) ValueBOx014EditMode = !ValueBOx014EditMode;
            if (GuiValueBox((Rectangle){ 56, 216, 48, 16 }, "x", &ValueBOx015Value, 0, 100, ValueBOx015EditMode)) ValueBOx015EditMode = !ValueBOx015EditMode;
            if (GuiValueBox((Rectangle){ 120, 216, 48, 16 }, "y", &ValueBOx016Value, 0, 100, ValueBOx016EditMode)) ValueBOx016EditMode = !ValueBOx016EditMode;
            if (GuiValueBox((Rectangle){ 184, 216, 48, 16 }, "z", &ValueBOx017Value, 0, 100, ValueBOx017EditMode)) ValueBOx017EditMode = !ValueBOx017EditMode;
            if (GuiValueBox((Rectangle){ 184, 168, 48, 16 }, "z", &ValueBOx018Value, 0, 100, ValueBOx018EditMode)) ValueBOx018EditMode = !ValueBOx018EditMode;
            if (GuiValueBox((Rectangle){ 120, 168, 48, 16 }, "y", &ValueBOx019Value, 0, 100, ValueBOx019EditMode)) ValueBOx019EditMode = !ValueBOx019EditMode;
            if (GuiValueBox((Rectangle){ 56, 168, 48, 16 }, "x", &ValueBOx020Value, 0, 100, ValueBOx020EditMode)) ValueBOx020EditMode = !ValueBOx020EditMode;
            GuiLabel((Rectangle){ 24, 168, 24, 16 }, "p");
            GuiLabel((Rectangle){ 240, 192, 24, 16 }, "v magnitude");
            GuiLabel((Rectangle){ 240, 216, 24, 16 }, "v magnitude");
            GuiGroupBox((Rectangle){ 8, 40, 280, 64 }, "Performance");
            GuiLabel((Rectangle){ 24, 48, 120, 24 }, "Frames Per Second");
            GuiLabel((Rectangle){ 24, 72, 120, 24 }, "Frametime");
            GuiLabel((Rectangle){ 200, 48, 72, 24 }, "60FPS");
            GuiLabel((Rectangle){ 200, 72, 72, 24 }, "0.00ms");
            if (GuiDropdownBox((Rectangle){ 184, 128, 80, 24 }, "color", &DropdownBox022Active, DropdownBox022EditMode)) DropdownBox022EditMode = !DropdownBox022EditMode;

            GuiUnlock();
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
