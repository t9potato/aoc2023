#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1(void);
int part2(void);

int main(int argc, char *argv[]) {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}

int part1(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int product = 1;
    int current = 0;
    int times[4] = { 0 };
    int distances[4] = { 0 };
    int type, index;
    type = index = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (isdigit(ch)) {
            current = current * 10 + ch - '0';
        } else if (current != 0) {
            if (!type) {
                times[index] = current;
            } else {
                distances[index] = current;
            }
            current = 0;
            index++;
        }
        if (ch == '\n' && type == 0) {
            type++;
            index = 0;
        }
    }
    for (int i = 0; i < index; i++) {
        int count = 0;
        for (int j = 0; j <= times[i]; j++) {
            if (distances[i] < j*(times[i] - j)) {
                count++;
            }
        }
        product *= count;
    }

    return product;
}

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    long type, time, distance;
    type = time = distance = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (isdigit(ch)) {
            if (!type) {
                time = time * 10 +  ch - '0';
            } else {
                distance = distance * 10 + ch - '0';
            }
        }
        if (ch == '\n') {
            type++;
        }
    }
    int count = 0;
    for (int j = 0; j <= time; j++) {
        if (distance < j*(time - j)) {
            count++;
        }
    }

    return count;
}
