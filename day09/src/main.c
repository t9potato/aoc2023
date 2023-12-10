#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long part1(void);
int part2(void);

int main(int argc, char *argv[]) {
    printf("Part 1: %ld\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}

long part1(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch, neg = 0;
    long sum = 0;
    int current = 0, index = 0;
    int* row = malloc(22*sizeof(int));
    memset(row, 0, 22*sizeof(int));
    while ((ch = fgetc(inFile)) != EOF) {
        if (isdigit(ch)) {
            current = 10*current + ch - '0';
        } else if (ch == ' ' || ch == '\n') {
            if (neg) {
                neg = 0;
                current *= -1;
            }
            row[index++] = current;
            current = 0;
        } else if (ch == '-') {
            neg = 1;
        }
        if (ch == '\n') {
            index--;
            int zero = 1;
            for (int i = index; zero; i--) {
                zero = 0;
                for (int j = 0; j < i; j++) {
                    row[j] = row[j+1] - row[j];
                    if (row[j] != 0) {
                        zero = 1;
                    }
                }
            }

            for (int i = 0; i <= index; i++) {
                sum += row[i];
            }
            
            index = 0;
            memset(row, 0, 21*sizeof(int));
        }
    }
    free(row);
    fclose(inFile);
    return sum;
}

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch, neg = 0;
    long sum = 0;
    int current = 0, index = 0;
    int* row = malloc(22*sizeof(int));
    memset(row, 0, 22*sizeof(int));
    while ((ch = fgetc(inFile)) != EOF) {
        if (isdigit(ch)) {
            current = 10*current + ch - '0';
        } else if (ch == ' ' || ch == '\n') {
            if (neg) {
                neg = 0;
                current *= -1;
            }
            row[index++] = current;
            current = 0;
        } else if (ch == '-') {
            neg = 1;
        }
        if (ch == '\n') {
            for (int i = 0; i < index/2; i++) {
                int tmp = row[i];
                row[i] = row[index-i-1];
                row[index-i-1] = tmp;
            }
            index--;
            int zero = 1;
            for (int i = index; zero; i--) {
                zero = 0;
                for (int j = 0; j < i; j++) {
                    row[j] = row[j+1] - row[j];
                    if (row[j] != 0) {
                        zero = 1;
                    }
                }
            }

            for (int i = 0; i <= index; i++) {
                sum += row[i];
            }
            
            index = 0;
            memset(row, 0, 21*sizeof(int));
        }
    }
    free(row);
    fclose(inFile);
    return sum;
}
