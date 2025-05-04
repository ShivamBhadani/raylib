#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<ray/raylib.h>

#define _USE_MATH_DEFINES

typedef struct{
    float real;
    float img;
}complex;

void dft(const float *in, complex *out, int N) {
    for (int k = 0; k < N; k++) {
        float sum_real = 0;
        float sum_imag = 0;
        for (int n = 0; n < N; n++) {
            float angle = 2 * M_PI * k * n / N;
            sum_real += in[n] * cos(angle);
            sum_imag -= in[n] * sin(angle);
        }
        out[k].real = sum_real;
        out[k].img = sum_imag;
    }
}

int main() {

    const int screenWidth = 2000;
    const int screenHeight = 1600;
    InitWindow(screenWidth,screenHeight,"discrete fourier transform");
    SetTargetFPS(90);
    
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    float signal[] = {1.0, 0.0, -1.0, 0.0};  
    int N = sizeof(signal) / sizeof(float);
    complex *result = malloc(N * sizeof(complex));

    dft(signal, result, N);

    for (int i = 0; i < N; i++) {
        printf("X[%d] = %.2f + %.2fi\n", i, result[i].real, result[i].img);
    }

    float dftt[4];

    for(int i=0;i<4;i++){
        dftt[i]=sqrt(result[i].img*result[i].img+result[i].real*result[i].real);
    }

    Vector2 centre = {screenWidth/2,screenHeight/2};
    Vector2 marky = {screenHeight/2-10,screenHeight/2+10};
    Vector2 markx = {screenWidth/2-10,screenWidth/2+10};

    while(!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();

        DrawLine(0,screenHeight/2,screenWidth,screenHeight/2,RAYWHITE);
        DrawLine(screenWidth/2,0,screenWidth/2,screenHeight,RAYWHITE);
        DrawCircle(centre.x-1,centre.y-1,4,GREEN);

        float width = screenWidth/20;
        int numpts = 20;
        for(int i=0;i<20;i++){
            DrawLine(i*width,marky.x,i*width,marky.y,RAYWHITE);
        }
        for(int i=0;i<16;i++){
            DrawLine(markx.x,i*width,markx.y,i*width,RAYWHITE);
        }

        for(int i=0;i<4;i++){
            DrawLine(screenWidth/2+i*width,screenHeight/2,screenWidth/2+i*width,screenHeight/2-width*signal[i],RED);
            DrawLine(screenWidth/2+i*width,screenHeight/2,screenWidth/2+i*width,screenHeight/2-width*dftt[i],BLUE);
        }

        EndDrawing();

    }
    CloseWindow();

    free(result);
    return 0;
}