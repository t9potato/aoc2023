#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    while ((ch = fgetc(inFile)) != EOF) {
    }
    return 0;
}
