#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

long part1(void);
long long part2(void);

int main(int argc, char *argv[]) {
    printf("Part 1: %ld\n", part1());
    printf("Part 2: %lld\n", part2());
    return 0;
}

typedef struct {
    long long x;
    long long y;
} position;

long long calculate(position* galaxy, int galCount) {
    if (galCount == 1)
        return 0;
    long long count = 0;
    for (int i = 1; i < galCount; i++) {
        count += llabs(galaxy[0].x-galaxy[i].x)+llabs(galaxy[0].y-galaxy[i].y);
    }
    return count + calculate(galaxy+1, galCount - 1);
}

long part1(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int width;
    int height = 1;
    int galCount = 0;
    for (width = 0; (ch = fgetc(inFile)) != '\n'; width++) {
        if (ch == '#')
            galCount++;
    }
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n')
            height++;
        else if (ch == '#')
            galCount++;
    }
    rewind(inFile);
    int i = 0, j = 0;
    position* galaxy = malloc(galCount*sizeof(position));
    char* vertOffset = malloc(height*sizeof(char));
    memset(vertOffset, 0, height*sizeof(char));
    char* horOffset = malloc(width*sizeof(char));
    memset(horOffset, 0, width*sizeof(char));
    char* vertEmpty = malloc(width*sizeof(char));
    memset(vertEmpty, 1, width*sizeof(char));
    char horEmpty = 1;
    int galIndex = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '#') {
            horEmpty = 0;
            vertEmpty[i] = 0;
            galaxy[galIndex].x = i;
            galaxy[galIndex].y = j;
            galIndex++;
        }
        if (ch == '\n') {
            if (horEmpty) {
                memset(vertOffset+j, vertOffset[j]+1, (height - j)*sizeof(char));
            }
            i = -1;
            j++;
            horEmpty = 1;
        }
        i++;
    }
    galIndex--;
    for (int i = 0; i < height; i++) {
        if (vertEmpty[i]) {
            memset(horOffset+i, horOffset[i]+1, (height-i)*sizeof(char));
        }
    }
    for (int i = 0; i < galCount; i++) {
        galaxy[i].y += vertOffset[galaxy[i].y];
        galaxy[i].x += horOffset[galaxy[i].x];
    }
    free(horOffset);
    free(vertOffset);
    free(vertEmpty);
    fclose(inFile);
    long ret = calculate(galaxy, galCount);
    free(galaxy);
    return ret;
}

long long part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int width;
    int height = 1;
    int galCount = 0;
    for (width = 0; (ch = fgetc(inFile)) != '\n'; width++) {
        if (ch == '#')
            galCount++;
    }
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n')
            height++;
        else if (ch == '#')
            galCount++;
    }
    rewind(inFile);
    int i = 0, j = 0;
    position* galaxy = malloc(galCount*sizeof(position));
    char* vertOffset = malloc(height*sizeof(char));
    memset(vertOffset, 0, height*sizeof(char));
    char* horOffset = malloc(width*sizeof(char));
    memset(horOffset, 0, width*sizeof(char));
    char* vertEmpty = malloc(width*sizeof(char));
    memset(vertEmpty, 1, width*sizeof(char));
    char horEmpty = 1;
    int galIndex = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '#') {
            horEmpty = 0;
            vertEmpty[i] = 0;
            galaxy[galIndex].x = i;
            galaxy[galIndex].y = j;
            galIndex++;
        }
        if (ch == '\n') {
            if (horEmpty) {
                memset(vertOffset+j, vertOffset[j]+1, (height - j)*sizeof(char));
            }
            i = -1;
            j++;
            horEmpty = 1;
        }
        i++;
    }
    galIndex--;
    for (int i = 0; i < height; i++) {
        if (vertEmpty[i]) {
            memset(horOffset+i, horOffset[i]+1, (height-i)*sizeof(char));
        }
    }
    for (int i = 0; i < galCount; i++) {
        galaxy[i].y += (1000000-1)*vertOffset[galaxy[i].y];
        galaxy[i].x += (1000000-1)*horOffset[galaxy[i].x];
    }
    free(horOffset);
    free(vertOffset);
    free(vertEmpty);
    fclose(inFile);
    long long ret = calculate(galaxy, galCount);
    free(galaxy);
    return ret;
}
