#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
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
    fseek(inFile, 0, SEEK_END);
    int len = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);
    int i = 0;
    char* contents = malloc(sizeof(char) * len+1);
    while ((ch = fgetc(inFile)) != EOF) {
        contents[i] = ch;
        i++;
    }
    fclose(inFile);
    contents[++i] = '\0';

    int width;
    for (width = 0; contents[width] != '\n'; width++);
    width++;

    int current, sum;
    current = sum = 0;
    bool part = false;
    for (int j = 0; j < i; j++) {
        if (isdigit(contents[j])) {
            if (!part) {
                if (j!=0 && contents[j-1] != '\n' && contents[j-1] != '.' && !isdigit(contents[j-1])) {
                    part = true;
                } else if (j!=i-1 && contents[j+1] != '\n' && contents[j+1] != '.' && !isdigit(contents[j+1])) {
                    part = true;
                } else if (j>width && contents[j-width] != '\n' && contents[j-width] != '.' && !isdigit(contents[j-width])) {
                    part = true;
                } else if (j>width && contents[j-width-1] != '\n' && contents[j-width-1] != '.' && !isdigit(contents[j-width-1])) {
                    part = true;
                } else if (j>width && contents[j-width+1] != '\n' && contents[j-width+1] != '.' && !isdigit(contents[j-width+1])) {
                    part = true;
                } else if (j<i-width-1 && contents[j+width] != '\n' && contents[j+width] != '.' && !isdigit(contents[j+width])) {
                    part = true;
                } else if (j<i-width-1 && contents[j+width-1] != '\n' && contents[j+width-1] != '.' && !isdigit(contents[j+width-1])) {
                    part = true;
                } else if (j<i-width-1 && contents[j+width+1] != '\n' && contents[j+width+1] != '.' && !isdigit(contents[j+width+1])) {
                    part = true;
                }
            }
            current = 10*current + contents[j] - '0';
        } else {
            if (current != 0) {
                if (part) {
                    sum += current;
                    part = !part;
                }
                current = 0;
            }
        }
    }
    return sum;
}

int expn(int b, int e) {
    int ans = 1;
    for (int i = 0; i < e; i++) {
        ans *= b;
    }
    return ans;
}

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    fseek(inFile, 0, SEEK_END);
    int len = ftell(inFile);
    fseek(inFile, 0, SEEK_SET);
    int i = 0;
    char* contents = malloc(sizeof(char) * len+1);
    while ((ch = fgetc(inFile)) != EOF) {
        contents[i] = ch;
        i++;
    }
    fclose(inFile);
    contents[++i] = '\0';

    int width;
    for (width = 0; contents[width] != '\n'; width++);
    width++;

    long sum = 0;
    for (int j = 0; j < i; j++) {
        if (contents[j] != '*') {
            continue;
        }

        int ul, u, ur, l, r, dl, d, dr;
        ul = u = ur = l = r = dl = d = dr = 0;
        if (j!=i-1 && isdigit(contents[j+1])) {
            r = 1;
        }
        if (j!=0 && isdigit(contents[j-1])) {
            l = 1;
        }
        if (j>width && isdigit(contents[j-width-1])) {
            ul = 1;
        }
        if (j>width && isdigit(contents[j-width])) {
            if (ul) ul = 0;
            u = 1;
        }
        if (j>width && isdigit(contents[j-width+1])) {
            if (!u) ur = 1;
        }
        if (j<i-width-1 && isdigit(contents[j+width-1])) {
            dl = 1;
        }
        if (j<i-width-1 && isdigit(contents[j+width])) {
            if (dl) dl = 0;
            d = 1;
        }
        if (j<i-width-1 && isdigit(contents[j+width+1])) {
            if (!d) dr = 1;
        }
        if (ul + u + ur + l + r + dl + d + dr != 2) {
            continue;
        }
        if (l) {
            l = 0;
            int p, q;
            for (p = j-1, q = 0; isdigit(contents[p]); p--, q++) {
                l += (contents[p]-'0')*expn(10, q);
            }
        } else l = 1;
        if (ul) {
            ul = 0;
            int p, q;
            for (p = j-1-width, q = 0; isdigit(contents[p]); p--, q++) {
                ul += (contents[p]-'0')*expn(10, q);
            }
        } else ul = 1;
        if (dl) {
            dl = 0;
            int p, q;
            for (p = j-1+width, q = 0; isdigit(contents[p]); p--, q++) {
                dl += (contents[p]-'0')*expn(10, q);
            }
        } else dl = 1;
        if (r) {
            r = 0;
            for (int i = j+1; isdigit(contents[i]); i++) {
                r = 10*r + contents[i]-'0';
            }
        } else r = 1;
        if (ur) {
            ur = 0;
            for (int i = j+1-width; isdigit(contents[i]); i++) {
                ur = 10*ur + contents[i]-'0';
            }
        } else ur = 1;
        if (dr) {
            dr = 0;
            for (int i = j+1+width; isdigit(contents[i]); i++) {
                dr = 10*dr + contents[i]-'0';
            }
        } else dr = 1;
        if (u) {
            u = 0;
            int p = j-width;
            while (isdigit(contents[--p]));
            while (isdigit(contents[++p])) {
                u = 10*u + contents[p]-'0';
            }
        } else u = 1;
        if (d) {
            d = 0;
            int p = j+width;
            while (isdigit(contents[--p]));
            while (isdigit(contents[++p])) {
                d = 10*d + contents[p]-'0';
            }
        } else d = 1;
        sum += ul * u * ur * l * r * dl * d * dr;
    }
    return sum;
}
