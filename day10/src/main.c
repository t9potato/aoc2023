#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} position;

int part1(position* corners, int* cornerCount);
int part2(position* corners, int cornerCount, int area);

int main(int argc, char *argv[]) {
    position* corners = malloc(10000*sizeof(position));
    int cornerCount = 0;
    int size = part1(corners, &cornerCount);
    printf("Part 1: %d\n", size/2);
    printf("Part 2: %d\n", part2(corners, cornerCount, size));
    return 0;
}

int eq(position a, position b) {
    if (a.x == b.x && a.y == b.y)
        return 1;
    return 0;
}

typedef enum {
    NONE,
    NORTH_SOUTH,
    EAST_WEST,
    NORTH_EAST,
    NORTH_WEST,
    SOUTH_EAST,
    SOUTH_WEST,
    START,
} dir;

typedef enum {
    WEST,
    EAST,
    NORTH,
    SOUTH,
} mov;

int part1(position* corners, int* cornerCount) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;

    position initial = {0, 0};
    int width = 0;
    int height = 1;
    for (; (ch = fgetc(inFile)) != '\n'; width++);
    for (; (ch = fgetc(inFile)) != EOF;)
        if (ch == '\n')
            height++;
    rewind(inFile);

    dir** feild = malloc(width*sizeof(int*));
    for (int i = 0; i < width; i++)
        feild[i] = malloc(height*sizeof(dir));

    for (int i = 0, j = 0; (ch = fgetc(inFile)) != EOF; i++) {
        switch (ch) {
            case '\n':
                i = -1;
                j++;
                break;
            case '|':
                feild[i][j] = NORTH_SOUTH; 
                break;
            case '-':
                feild[i][j] = EAST_WEST; 
                break;
            case 'L':
                feild[i][j] = NORTH_EAST; 
                break;
            case 'J':
                feild[i][j] = NORTH_WEST; 
                break;
            case 'F':
                feild[i][j] = SOUTH_EAST; 
                break;
            case '7':
                feild[i][j] = SOUTH_WEST; 
                break;
            case '.':
                feild[i][j] = NONE;
                break;
            case 'S':
                feild[i][j] = START;
                initial.x = i;
                initial.y = j;
                break;
        }
    }

    position current;
    mov prev;
    if (feild[initial.x][initial.y-1] == NORTH_SOUTH ||
        feild[initial.x][initial.y-1] == SOUTH_EAST ||
        feild[initial.x][initial.y-1] == SOUTH_WEST) {
        current.x = initial.x;
        current.y = initial.y-1;
        prev = SOUTH;
    } else if (feild[initial.x][initial.y+1] == NORTH_SOUTH ||
        feild[initial.x][initial.y+1] == NORTH_EAST ||
        feild[initial.x][initial.y+1] == NORTH_WEST) {
        current.x = initial.x;
        current.y = initial.y+1;
        prev = NORTH;
    } else if (feild[initial.x-1][initial.y] == EAST_WEST ||
        feild[initial.x-1][initial.y] == SOUTH_WEST ||
        feild[initial.x-1][initial.y] == NORTH_WEST) {
        current.x = initial.x-1;
        current.y = initial.y;
        prev = EAST;
    } else if (feild[initial.x+1][initial.y] == EAST_WEST ||
        feild[initial.x+1][initial.y] == SOUTH_EAST ||
        feild[initial.x+1][initial.y] == NORTH_EAST) {
        current.x = initial.x+1;
        current.y = initial.y;
        prev = WEST;
    }

    int i;
    *cornerCount = 0;
    mov init = prev;
    for (i = 1; !eq(current, initial); i++) {
        switch(feild[current.x][current.y]) {
            case NORTH_EAST:
                corners[*cornerCount].x = current.x;
                corners[*cornerCount].y = current.y;
                (*cornerCount)++;
                if (prev == NORTH) {
                    prev = WEST;
                    current.x++;
                } else {
                    prev = SOUTH;
                    current.y--;
                }
                break;
            case NORTH_SOUTH:
                if (prev == NORTH)
                    current.y++;
                else
                    current.y--;
                break;
            case NORTH_WEST:
                corners[*cornerCount].x = current.x;
                corners[*cornerCount].y = current.y;
                (*cornerCount)++;
                if (prev == NORTH) {
                    prev = EAST;
                    current.x--;
                } else {
                    prev = SOUTH;
                    current.y--;
                }
                break;
            case SOUTH_EAST:
                corners[*cornerCount].x = current.x;
                corners[*cornerCount].y = current.y;
                (*cornerCount)++;
                if (prev == SOUTH) {
                    prev = WEST;
                    current.x++;
                } else {
                    prev = NORTH;
                    current.y++;
                }
                break;
            case SOUTH_WEST:
                corners[*cornerCount].x = current.x;
                corners[*cornerCount].y = current.y;
                (*cornerCount)++;
                if (prev == SOUTH) {
                    prev = EAST;
                    current.x--;
                } else {
                    prev = NORTH;
                    current.y++;
                }
                break;
            case EAST_WEST:
                if (prev == WEST)
                    current.x++;
                else
                    current.x--;
                break;
            default:
                printf("Failed\n");
                exit(1);
        }
    }
    if (!((prev == EAST && init == WEST) ||
        (prev == WEST && init == EAST) ||
        (prev == SOUTH && init == NORTH) ||
        (prev == NORTH && init == SOUTH))){
                corners[*cornerCount].x = current.x;
                corners[*cornerCount].y = current.y;
                (*cornerCount)++;
    }

    (*cornerCount)--;
    for (int i = 0; i < width; i++)
        free(feild[i]);
    free(feild);
    fclose(inFile);
    return i;
}

int part2(position* corners, int cornerCount, int borderArea) {
    int area = 0;
    for (int i = 0; i < cornerCount; i++) {
        area += (corners[i].x-corners[i+1].x)*(corners[i].y+corners[i+1].y);
    }
    area += (corners[cornerCount].x-corners[0].x)*(corners[cornerCount].y+corners[0].y);
    area /= 2;
    area = abs(area);

    return area - (borderArea/2) + 1;
}
