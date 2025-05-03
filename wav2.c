#include<stdio.h>
#include<assert.h>
#include<stdint.h>
#include<string.h>
#include<ray/raylib.h>

#define FB file+bytes_read

char *handlefileopen(char* filename);
void handlefileclose(void);

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
    (void)shift(&argc,&argv);
    char *audiofile = shift(&argc,&argv);

    char *file = handlefileopen(audiofile);
    int bytes_read=0;
    char RIFF[5]={0};
    int size=0;
    int fmtsize=0;
    wav_header wh={0};
    fmt_header fh={0};
    fmt_chunk  fc={0};
    data_chunk dc={0};
    memcpy(&wh,FB,sizeof wh);
    bytes_read+=sizeof wh;
    memcpy(&fh,FB,sizeof fh);
    bytes_read+=sizeof fh;
    memcpy(&fc,FB,sizeof fc);
    bytes_read+=sizeof fc;
    memcpy(&dc,FB,sizeof dc);
    bytes_read+=sizeof dc;

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
    printf("data: %.4s\n",dc.data);
    printf("chunk size: %u\n",dc.chunk_size);
    printf("num chunks: %u\n",dc.chunk_size/4);
    float length = (float)dc.chunk_size/(4*fc.sample_rate);
    printf("audio length: %fs\n",length);
    assert(fc.bits_per_sample == 16);

    const int screenWidth = 2000;
    const int screenHeight = 1600;
    int ndata=screenWidth*fc.channels;

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

        for (int i = 0; i<ndata&&bytes_read<wh.wav_size; i += fc.channels) {
            int16_t sample = *(int16_t*)(file+bytes_read);
            bytes_read+=2;
            int j = scale * sample;
            DrawLine(i, (screenHeight -j) / 2, i , (screenHeight + j) / 2, j>screenHeight/4?RED:BLUE);
        }
        EndDrawing();
    }
    UnloadMusicStream(music);
    CloseAudioDevice();
    handlefileclose();
    CloseWindow();

    return 0;

}