#include "ray/raylib.h"
int main(void){
    const int width = 1440;
    const int height = 1080;
	  SetConfigFlags(FLAG_MSAA_4X_HINT);   // Enables 4x MSAA
    InitWindow(width, height, "Bouncing Ball Simulation with Paddle");
    Vector2 ballpos = { (float)width / 2, (float)height / 2 }; 
    float ballrad = 20.0f;  
    Vector2 ballspeed = { 9.0f, 9.0f };  
    float padwid = 150.0f;
    float padhigh = 10.0f;
    Vector2 padpos = { (float)width / 2 - padwid / 2, height - padhigh - 10.0f }; 
    float padspeed = 10.0f; 
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        if (IsKeyDown(KEY_RIGHT)) padpos.x += padspeed;  
        if (IsKeyDown(KEY_LEFT)) padpos.x -= padspeed;  
        if (padpos.x < 0) padpos.x = 0;
        if (padpos.x + padwid > width) padpos.x = width - padwid;
        ballpos.x += ballspeed.x;
        ballpos.y += ballspeed.y;
        if (ballpos.x - ballrad <= 0 || ballpos.x + ballrad >= width){
            ballspeed.x = -ballspeed.x; 
        }
        if (ballpos.y - ballrad <= 0){
            ballspeed.y = -ballspeed.y; 
        }
        if (ballpos.y + ballrad >= padpos.y && ballpos.x >= padpos.x && ballpos.x <= padpos.x + padwid){
            ballspeed.y = -ballspeed.y;  
        }
        if (ballpos.y + ballrad > height){
            ballpos = (Vector2){ width / 2, height / 2 };
            ballspeed = (Vector2){ 4.0f, 4.0f }; 
        }
        BeginDrawing();
        ClearBackground(BLACK); 
        DrawCircleV(ballpos, ballrad, RAYWHITE);
        DrawRectangleV(padpos, (Vector2){ padwid, padhigh }, GREEN);  
        DrawText("Use Left/Right Arrows to Move the Paddle!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}