#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1(void);
int part2(void);

int main(int argc, char *argv[]) {
    printf("Part 1: %d", part1());
    printf("Part 2: %d", part2());
    return 0;
}

int part1(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    while ((ch = fgetc(inFile)) != EOF) {
    }
}

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    while ((ch = fgetc(inFile)) != EOF) {
    }
}
