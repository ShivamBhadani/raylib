#include<ray/raylib.h>
#include<stdio.h>
#include<string.h>

int main(void){
    const int screenWidth = 2000;
    const int screenHeight = 1600;
    
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth,screenHeight,"pong game");
    SetTargetFPS(90);

    Vector2 rectpos = {screenWidth/2,screenHeight*.25};
    Vector2 rectshape = {20.0f,screenHeight*.75};
    Vector2 ballpos,ballinit ={screenWidth/2+30,100};
    ballpos = ballinit;
    float ballrad = 25.0f;
    float padwid = 150.0f;
    float padhigh = 10.0f;
    Vector2 padposL = { 0.0f, 0.0f }; 
    Vector2 padposR = { screenWidth-padhigh, 0.0f };
    Vector2 padshape = {padhigh,padwid};
    float padspeed = 10.0f;
    Vector2 ballspeed ={padspeed,3};
    Rectangle padL= {padposL.x,padposL.y,padhigh,padwid};
    Rectangle padR= {padposR.x,padposR.y,padhigh,padwid};
    float xl = rectpos.x-rectshape.x/2;
    float xr = rectpos.x+rectshape.x/2;
    Rectangle rect= {xl,rectpos.y,rectshape.x,rectshape.y};
    
    int scoreL=0,scoreR=0;
    char buf[20]={0};

    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
        snprintf(buf,sizeof buf,"score blue: %d",scoreL);
        DrawText(buf,20,20,30,GRAY);
        snprintf(buf,sizeof buf,"score green: %d",scoreR);
        DrawText(buf,screenWidth/2+20,20,30,GRAY);
        
        DrawRectangleRounded(rect,0.5,0,RAYWHITE);
        DrawRectangleRounded(padR,0.5,0,GREEN);
        DrawRectangleRounded(padL,0.5,0,BLUE);
        DrawCircleV(ballpos,ballrad,RED);
        ballpos.x+=ballspeed.x;
        ballpos.y+=ballspeed.y;
        if (IsKeyDown(KEY_DOWN)&&ballpos.x<screenWidth/2){
            padL.y+=padspeed;
        }
        if (IsKeyDown(KEY_DOWN)&&ballpos.x>screenWidth/2){
            padR.y+=padspeed;
        }
        if (IsKeyDown(KEY_UP)&&ballpos.x<screenWidth/2){
            padL.y-=padspeed;
        }
        if (IsKeyDown(KEY_UP)&&ballpos.x>screenWidth/2){
            padR.y-=padspeed;
        }
        if((ballpos.y+ballrad)==rect.y&&ballpos.x>xl&&ballpos.x<xr){
            ballspeed.y = -ballspeed.y;
            ballspeed.x = -ballspeed.x;
        }
        if((ballpos.x-ballrad)<0||(ballpos.x+ballrad)>screenWidth){
            if((ballpos.y>=padL.y && ballpos.x<screenWidth/2 && ballpos.y<=(padL.y+padL.height))||(ballpos.y>=padR.y && ballpos.x>screenWidth/2 && ballpos.y<=(padR.y+padR.height)))
                ballspeed.x=-ballspeed.x;
            else{
                ballpos.x<screenWidth/2?scoreR++:scoreL++;
                ballpos=ballinit;
            }
        }
        // if(ballpos.y>=padR.y&&ballpos.y<=(padR.y+padR.height)&&(ballpos.x+ballrad)>screenWidth)ballspeed.x=-ballspeed.x;
        if((ballpos.y+ballrad)>screenHeight||(ballpos.y-ballrad)<0)ballspeed.y=-ballspeed.y;
        if((ballpos.x+ballrad)>xl && (ballpos.x-ballrad)<xr && (ballpos.y+ballrad)>rect.y)ballspeed.x=-ballspeed.x;
        // if(IsKeyDown(KEY_RIGHT))ballpos.x+=10;
        // if(IsKeyDown(KEY_LEFT))ballpos.x-=10;
        if((padL.y+padwid)>screenHeight)padL.y=(screenHeight-padwid);
        if(padL.y<0)padL.y=0;
        if((padR.y+padwid)>screenHeight)padR.y=(screenHeight-padwid);
        if(padR.y<0)padR.y=0;
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}