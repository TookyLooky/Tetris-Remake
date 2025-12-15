#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime =  0;

bool EventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;

    }
    return false;

#if defined(WIN32) && !defined(_DEBUG)
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif    
}
int main() 
{
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/PressStart2P-Regular.ttf", 64,0,0);

    Game game = Game();

    while(WindowShouldClose() == false){
        UpdateMusicStream(game.music);
        game.HandleInput();
        if(EventTriggered(0.35)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {340,20}, 23, 2, WHITE);
        DrawTextEx(font, "Next", {355,175}, 25, 2, WHITE);
        if(game.gameOver){
            DrawTextEx(font, "GAME \n OVER", {330,450}, 25, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
       

        DrawTextEx(font, scoreText, {320 + (190 - textSize.x) / 2, 70}, 27, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();
        EndDrawing();

    }

    CloseWindow();
}