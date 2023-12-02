#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int part1(void);
int part2(void);

int main(int argc, char *argv[]) {
    printf("%d\n", part1());
    printf("%d\n", part2());
    return 0;
}

int part1(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int first, last, ans;
    first = last = ans = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            ans += (10*first + last);
            first = last = 0;
        } else if (isdigit(ch)) {
            if (first == 0) {
                first = ch - 48;
            }
            last = ch - 48;
        }
    }
    fclose(inFile);
    return ans;
}

int check_stack(char* stack) {
    if (strstr(stack, "one")) {
        return 1;
    } else if (strstr(stack, "two")) {
        return 2;
    } else if (strstr(stack, "three")) {
        return 3;
    } else if (strstr(stack, "four")) {
        return 4;
    } else if (strstr(stack, "five")) {
        return 5;
    } else if (strstr(stack, "six")) {
        return 6;
    } else if (strstr(stack, "seven")) {
        return 7;
    } else if (strstr(stack, "eight")) {
        return 8;
    } else if (strstr(stack, "nine")) {
        return 9;
    }
    return 0;
}

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int first, last, ans;
    first = last = ans = 0;
    char* stack = malloc(7);
    stack = memset(stack, 0, 6);
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            ans += (10*first + last);
            first = last = 0;
            stack = memset(stack, 0, 6);
        } else if (isdigit(ch)) {
            if (first == 0)
                first = ch - 48;
            last = ch - 48;
            stack = memset(stack, 0, 6);
        } else {
            if (strlen(stack) != 5) {
                stack[strlen(stack)] = ch;
            } else {
                for (int i = 1; i < 5; i++) {
                    stack[i-1] = stack[i];
                }
                stack[4] = ch;
            }
            int tmp = check_stack(stack);
            if (tmp != 0) {
                if (first == 0) {
                    first = tmp;
                }
                last = tmp;
            }
        }
    }
    free(stack);
    fclose(inFile);
    return ans;
}
