#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1(void);
int part2(void);

int main(int argc, char* argv[]) {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());
    return 0;
}

int part1(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int current, sum, lineTotal, check;
    current = sum = lineTotal = check = 0;
    int* valid = malloc(11*sizeof(int));
    memset(valid, 0, 11*sizeof(int));
    
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == 'C') {
            // Skip to values, ignore numbers
            while (fgetc(inFile) != ':');
            memset(valid, 0, 10*sizeof(int));
            sum += lineTotal;
            check = lineTotal = 0;
        } else if (isdigit(ch)) {
            current = 10*current + (ch-'0');
        } else {
            if (current && !check) {
                int i;
                for (i = 0; valid[i] != 0; i++);
                valid[i] = current;
                current = 0;
            } else if (current) {
                for (int i = 0; valid[i] != 0; i++) {
                    if (valid[i] == current) {
                        lineTotal = (lineTotal ? 2*lineTotal : 1);
                        break;
                    }
                }
                current = 0;
            }
            if (ch == '|') {
                check = 1;
            }
        }
    }
    sum += lineTotal;
    return sum;
}

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    unsigned char lines = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    int* cards = malloc(lines*sizeof(int));
    for (int i = 0; i < lines; i++) {
        cards[i] = 1;
    }

    int current,  lineTotal, check, i;
    current = lineTotal = check = i = 0;
    int* valid = malloc(11*sizeof(int));
    memset(valid, 0, 11*sizeof(int));
    
    fseek(inFile, 0, SEEK_SET);
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == 'C') {
            // Skip to values, ignore numbers
            while (fgetc(inFile) != ':');
        } else if (isdigit(ch)) {
            current = 10*current + (ch-'0');
        } else {
            if (current && !check) {
                int i;
                for (i = 0; valid[i] != 0; i++);
                valid[i] = current;
                current = 0;
            } else if (current) {
                for (int i = 0; valid[i] != 0; i++) {
                    if (valid[i] == current) {
                        lineTotal += 1;
                        break;
                    }
                }
                current = 0;
            }
            if (ch == '|') {
                check = 1;
            }
            if (ch == '\n') {
                memset(valid, 0, 10*sizeof(int));
                for (int j = 1; j <= lineTotal; j++) {
                    cards[i+j] += cards[i];
                }
                check = lineTotal = 0;
                i++;
            }
        }
    }
    long sum = 0;;
    for (int j = 0; j < lines; j++) {
        sum += cards[j];
    }
    return sum;
}
