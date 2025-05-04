#include<ray/raylib.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(void){
    float screenwidth=2000.0f;
    float screenheight=1600.0f;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenwidth,screenheight,"sine wave");
    SetTargetFPS(90);

    int count;
    scanf("%d",&count);
    float *values=malloc(count*sizeof(float));
    float precision=(float)4*M_PI/count;
    printf("%f\n",precision);
    for(int i=0;i<count;i++){
        values[i]=sinf(-2*M_PI+precision*i);
    }
    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
        DrawLine(0,screenheight/2,screenwidth,screenheight/2,RAYWHITE);
        for(int i=0;i<count;i++){
            DrawLine(i,screenheight/2,i,screenheight/2-values[i]*screenheight/5,RED);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}