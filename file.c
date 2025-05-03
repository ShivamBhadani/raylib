#include<windows.h>
#include<stdio.h>

HANDLE hMap;
HANDLE hFile;
void *data;

char* handlefileopen(char* filename){
    hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to open file\n");
        return NULL;
    }

    hMap = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hMap == NULL) {
        printf("Failed to create file mapping\n");
        CloseHandle(hFile);
        return NULL;
    }

    data = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
    if (data == NULL) {
        printf("Failed to map view of file\n");
        CloseHandle(hMap);
        CloseHandle(hFile);
        return NULL;
    }
   
    return (char*)data;
}

void handlefileclose(void){
    UnmapViewOfFile(data);
    CloseHandle(hMap);
    CloseHandle(hFile);
}