#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
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
    int sum = 0;
    char ch;
    int val = 0;
    int index = 0;
    bool valid = true;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == 'G') {
            while ((ch = fgetc(inFile)) != ':');
            if (valid) {
                sum += index;
            }
            index++;
            val = 0;
            valid = true;
        } else if (isdigit(ch)) {
            val = 10*val + (ch-'0');
        } else if (valid){
            switch (ch) {
                case 'r': {
                    if (val > 12) {
                        valid = false;
                    }
                    val = 0;
                }
                case 'g': {
                    if (val > 13) {
                        valid = false;
                    }
                    val = 0;
                }
                case 'b': {
                    if (val > 14) {
                        valid = false;
                    }
                    val = 0;
                }
            }
        }
    }
    if (valid) {
        sum += index;
    }
    fclose(inFile);
    return sum;
}

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int val, sum, red, green, blue;
    val = red = sum = green = blue = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == 'G') {
            while ((ch = fgetc(inFile)) != ':');
            sum += red*green*blue;
            red = green = blue = val = 0;
        } else if (isdigit(ch)) {
            val = 10*val + (ch-'0');
        } else {
            switch (ch) {
                case 'r': {
                    if (val > red) {
                        red = val;
                    }
                    val = 0;
                }
                case 'g': {
                    if (val > green) {
                        green = val;
                    }
                    val = 0;
                }
                case 'b': {
                    if (val > blue) {
                        blue = val;
                    }
                    val = 0;
                }
            }
        }
    }
    sum += red*green*blue;
    fclose(inFile);
    return sum;
}
