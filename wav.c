#include<stdio.h>
#include<assert.h>
#include<stdint.h>
#include<math.h>
#include<ray/raylib.h>

static char *shift(int* argc, char*** argv){
  assert(*argc>0);
  char* result=**argv;
  *argc-=1;
  *argv+=1;
  return result;
}

typedef struct{
    char riff[4];
    unsigned int wav_size;
    char wave[4];
}wav_header;

typedef struct{
    char fmt[4];
    unsigned int size;
}fmt_header;

typedef struct{
    unsigned short int aud_fmt;
    unsigned short int channels;
    unsigned int sample_rate;
    unsigned int byte_rate;
    unsigned short int block_align;
    unsigned short int bits_per_sample;
}fmt_chunk;

typedef struct{
    char data[4];
    unsigned int chunk_size;
}data_chunk;

int main(int argc, char *argv[]){
    assert(argc>=2);
    (void)shift(&argc,&argv);\
    char *audiofile = shift(&argc,&argv);
    FILE *file = fopen(audiofile,"rb");
    char RIFF[5]={0};
    int size=0;
    int fmtsize=0;
    wav_header wh={0};
    fmt_header fh={0};
    fmt_chunk  fc={0};
    fread(&wh,1,12,file);
    fread(&fh,1,8,file);
    fread(&fc,1,16,file);
    printf("riff: %.4s\n",wh.riff);
    printf("file size: %u\n",wh.wav_size);
    printf("wave: %.4s\n",wh.wave);
    printf("fmt: %.4s\n",fh.fmt);
    printf("fmt header size: %u\n",fh.size);
    printf("audio format: %hu\n",fc.aud_fmt);
    printf("channels: %hu\n",fc.channels);
    printf("sample rate: %u\n",fc.sample_rate);
    printf("byte rate: %u\n",fc.byte_rate);
    printf("block align: %hu\n",fc.block_align);
    printf("bits per sample: %hu\n",fc.bits_per_sample);
    data_chunk dc={0};
    fread(&dc,1,8,file);
    printf("data: %.4s\n",dc.data);
    printf("chunk size: %u\n",dc.chunk_size);
    printf("num chunks: %u\n",dc.chunk_size/4);
    float length = (float)dc.chunk_size/(4*fc.sample_rate);
    printf("audio length: %fs\n",length);

    
    const int screenWidth = 2000;
    const int screenHeight = 1600;
    int ndata=screenWidth*fc.channels;
    uint16_t data[ndata];
    
    float scale = (float)screenHeight/(1<<16)/2;
    printf("scale: %f\n",scale);
    
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitWindow(screenWidth,screenHeight,"wav");
    SetTargetFPS(22);

    InitAudioDevice();
    Music music = LoadMusicStream(audiofile);
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        UpdateMusicStream(music);
    
        int samplesRead = fread(data, sizeof(short), ndata, file);
        if (samplesRead == 0) {
            rewind(file); 
            continue;
        }
        for (int i = 0; i < samplesRead; i += fc.channels) {
            int j = scale * data[i];
            DrawLine(i, (screenHeight -j) / 2, i , (screenHeight + j) / 2, j>screenHeight/4?RED:BLUE);
        }
    
        EndDrawing();
    }
    UnloadMusicStream(music);
    CloseAudioDevice();
    fclose(file);
    CloseWindow();

    return 0;

}