#include <ctype.h>
#include <limits.h>
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
    long* seeds = malloc(20*sizeof(long));
    memset(seeds, 0, 20*sizeof(long));
    long* mached = malloc(20*sizeof(long));
    long state, current, lDest, lSource, lLength, lState, length;
    state = -1;
    length = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (isalpha(ch)) {
            while (fgetc(inFile) != ':');
            state++;
            current = lDest = lSource = lLength = lState = 0;
            memset(mached, 0, 20*sizeof(long));
            continue;
        } else if (ch == ' ' && state) {
            if (lState == 0)
                lDest = current;
            else if (lState == 1)
                lSource = current;
            current = 0;
            lState++;
            continue;
        } else if (isdigit(ch)) {
            current = current * 10 + ch -'0';
            continue;
        }
        if (!state) {
            if (current) {
                seeds[length] = current;
                length = ++lState;
                current = 0;
            }
            continue;
        }
        lLength = current;
        current = 0;
        for (int i = 0; i < length; i++) {
            if (mached[i])
                continue;
            if (seeds[i] >= lSource && seeds[i] < lSource + lLength) {
                seeds[i] = lDest + seeds[i] - lSource;
                mached[i] = 1;
            }
        }
        lState = 0;
    }
    long min = LONG_MAX;
    for (int i = 0; i < length; i++) {
        if (seeds[i] < min)
            min = seeds[i];
    }
    return min;
}

typedef struct {
    long low;
    long high;
} range;

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    range* seeds = malloc(200*sizeof(range));
    memset(seeds, 0, 200*sizeof(range));
    long* mached = malloc(200*sizeof(long));
    long state, current, lDest, lSource, lLength, lState, length;
    state = -1;
    length = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (isalpha(ch)) {
            while (fgetc(inFile) != ':');
            state++;
            current = lDest = lSource = lLength = lState = 0;
            memset(mached, 0, 200*sizeof(long));
            continue;
        } else if (ch == ' ' && state) {
            if (lState == 0)
                lDest = current;
            else if (lState == 1)
                lSource = current;
            current = 0;
            lState++;
            continue;
        } else if (isdigit(ch)) {
            current = current * 10 + ch -'0';
            continue;
        }
        if (!state) {
            if (current && seeds[length].low) {
                seeds[length].high = seeds[length].low + current - 1;
                length = ++lState;
            } else if (current) {
                seeds[length].low = current;
            }
            current = 0;
            continue;
        }
        lLength = current;
        current = 0;
        for (int i = 0; i < length; i++) {
            if (mached[i])
                continue;
            if (seeds[i].low >= lSource && seeds[i].high < lSource + lLength) {
                seeds[i].low = lDest + seeds[i].low - lSource;
                seeds[i].high = lDest + seeds[i].high - lSource;
                mached[i] = 1;
            } else if (seeds[i].low >= lSource && seeds[i].low < lSource + lLength) {
                seeds[length].low = lDest + seeds[i].low - lSource;
                seeds[length].high = lDest + lLength - 1;
                seeds[i].low = lSource + lLength;
                mached[length] = 1;
                length++;
            } else if (seeds[i].high >= lSource && seeds[i].high < lSource + lLength) {
                seeds[length].low = lDest;
                seeds[length].high = lDest + seeds[i].high - lSource;
                seeds[i].high = lSource - 1;
                mached[length] = 1;
                length++;
            } else if (seeds[i].low < lSource && seeds[i].high >= lSource + lLength) {
                seeds[length].low = lDest;
                seeds[length].high = lDest + lLength - 1;
                mached[length] = 1;
                length++;
                seeds[length].low = lSource + lLength;
                seeds[length].high = seeds[i].high;
                length++;
                seeds[i].high = lSource - 1;
            }
        }
        lState = 0;
    }
    long min = LONG_MAX;
    for (int i = 0; i < length; i++) {
        if (seeds[i].low < min)
            min = seeds[i].low;
    }
    return min;
}
