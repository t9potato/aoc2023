#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int part1(void);
long part2(void);

int main(void) {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %ld\n", part2());
    return 0;
}

int lettersToIndex(char letters[3]) {
    return (letters[0] - 'A') * 676 + (letters[1] - 'A') * 26 + letters[2] - 'A';
}

typedef struct value {
    int left;
    int right;
} value;

int part1(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int goal = lettersToIndex("ZZZ");
    int index, length;
    index = 0;
    length = 20;
    bool* instructions = malloc(length*sizeof(bool));
    while ((ch = fgetc(inFile)) != '\n') {
        if (ch == 'L') {
            instructions[index] = false;
        } else {
            instructions[index] = true;
        }
        index++;
        if (index == length) {
            length *= 2;
            if ((instructions = realloc(instructions, length*sizeof(bool))) == NULL) {
                exit(1);
            }
        }
    }
    fgetc(inFile);

    char stack[3] = { -1, -1, -1 };
    value network[17575];
    int val, left, right, stackIndex;
    val = left = right = stackIndex = 0;
    int key = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            network[val].left = left;
            network[val].right = right;
        } else if (ch == '=') {
            val = lettersToIndex(stack);
            stackIndex = 0;
        } else if (ch == ',') {
            left = lettersToIndex(stack);
            stackIndex = 0;
        } else if (ch == ')') {
            right = lettersToIndex(stack);
            stackIndex = 0;
        } else if (isupper(ch)) {
            stack[stackIndex] = ch;
            stackIndex++;
        }
    }
    int i = 0;
    for (; key != goal; i++) {
        if (instructions[i%index]) {
            key = network[key].right;
        } else { 
            key = network[key].left;
        }
    }

    free(instructions);
    fclose(inFile);
    return i;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
long lcm(long a, long b) {
    return (a / gcd(a, b)) * b;
} 

long part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int index, length;
    index = 0;
    length = 20;
    bool* instructions = malloc(length*sizeof(bool));
    while ((ch = fgetc(inFile)) != '\n') {
        if (ch == 'L') {
            instructions[index] = false;
        } else {
            instructions[index] = true;
        }
        index++;
        if (index == length) {
            length *= 2;
            if ((instructions = realloc(instructions, length*sizeof(bool))) == NULL) {
                exit(1);
            }
        }
    }
    fgetc(inFile);

    char stack[3] = { -1, -1, -1 };
    value network[17575];
    int val, left, right, stackIndex;
    val = left = right = stackIndex = 0;
    int* keys = malloc(10*sizeof(int));
    int keysIndex = 0;
    int keysLen = 10;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            network[val].left = left;
            network[val].right = right;

            if (val%26 == 0) {
                keys[keysIndex++] = val;
                if (keysLen == keysIndex) {
                    keysLen *= 2;
                    if ((keys = realloc(keys, keysLen*sizeof(int))) == NULL) {
                        exit(0);
                    }
                }
            }
        } else if (ch == '=') {
            val = lettersToIndex(stack);
            stackIndex = 0;
        } else if (ch == ',') {
            left = lettersToIndex(stack);
            stackIndex = 0;
        } else if (ch == ')') {
            right = lettersToIndex(stack);
            stackIndex = 0;
        } else if (isupper(ch)) {
            stack[stackIndex] = ch;
            stackIndex++;
        }
    }

    int* j = malloc(keysIndex*sizeof(int));
    memset(j, 0, keysIndex*sizeof(int));
    for (int i = 0; i < keysIndex; i++) {
        int key = keys[i];
        for (; key%26 != 25; j[i]++) {
            if (instructions[j[i]%index]) {
                key = network[key].right;
            } else { 
                key = network[key].left;
            }
        }
    }
    long result = j[0];
    printf("%d\n", j[0]);
    for (int k = 1; k < keysIndex; k++) {
        result = lcm(result, j[k]);
    }

    free(instructions);
    fclose(inFile);
    return result;
}
