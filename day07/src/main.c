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

typedef enum {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
} type;

typedef struct order {
    char hand[5];
    type type;
    int bid;
} order;

int sort(const void* a, const void* b) {
    order* first = (order*)a;
    order* second = (order*)b;
    if (first->type != second->type) {
        return first->type - second->type;
    }
    for (int i = 0; i < 5; i++) {
        if (first->hand[i] != second->hand[i])
            return first->hand[i] - second->hand[i];
    }
    return 0;
}

long part1(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int length = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            length++;
        }
    }
    rewind(inFile);

    order rounds[1000];
    memset(rounds, 0, 1000*sizeof(order));
    int i = 0;
    int j = 0;
    int set = 0;
    char hand[13];
    memset(hand, 0, 13*sizeof(char));
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            char sec, max;
            sec = max = 0;
            for (int j = 0; j < 13; j++) {
                if (hand[j] > max) {
                    sec = max;
                    max = hand[j];
                } else if (hand[j] > sec) {
                    sec = hand[j];
                }
            }
            if (max == 5)
                rounds[i].type = FIVE_OF_A_KIND;
            else if (max == 4)
                rounds[i].type = FOUR_OF_A_KIND;
            else if (max == 3 && sec == 2)
                rounds[i].type = FULL_HOUSE;
            else if (max == 3)
                rounds[i].type = THREE_OF_A_KIND;
            else if (sec == 2)
                rounds[i].type = TWO_PAIR;
            else if (max == 2)
                rounds[i].type = PAIR;
            else
                rounds[i].type = HIGH_CARD;

            memset(hand, 0, 13*sizeof(char));
            j = set = 0;
            i++;
        } else if (ch == ' ') {
            set++;
        } else if (set)
            rounds[i].bid = rounds[i].bid*10 + ch-'0';
        else {
            if (isdigit(ch)) {
                rounds[i].hand[j] = ch - '0';
            } else if (ch == 'T') {
                rounds[i].hand[j] = 10;
            } else if (ch == 'J') {
                rounds[i].hand[j] = 11;
            } else if (ch == 'Q') {
                rounds[i].hand[j] = 12;
            } else if (ch == 'K') {
                rounds[i].hand[j] = 13;
            } else if (ch == 'A') {
                rounds[i].hand[j] = 14;
            }
            hand[rounds[i].hand[j]-2]++;
            j++;
        }
            
    }

    qsort(rounds, length, sizeof(order), sort);

    long sum = 0;
    for (int i = 0; i < length; i++) {
        sum += (1+i)*rounds[i].bid;
    }

    return sum;
}

int part2(void) {
    FILE* inFile = fopen("input/in.txt", "r");
    char ch;
    int length = 0;
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            length++;
        }
    }
    rewind(inFile);

    order rounds[1000];
    memset(rounds, 0, 1000*sizeof(order));
    int i = 0;
    int j = 0;
    int set = 0;
    int wildcard = 0;
    char hand[12];
    memset(hand, 0, 12*sizeof(char));
    while ((ch = fgetc(inFile)) != EOF) {
        if (ch == '\n') {
            char sec, max;
            sec = max = 0;
            for (int j = 0; j < 12; j++) {
                if (hand[j] > max) {
                    sec = max;
                    max = hand[j];
                } else if (hand[j] > sec) {
                    sec = hand[j];
                }
            }
            if (max == 5)
                rounds[i].type = FIVE_OF_A_KIND;
            else if (max == 4)
                rounds[i].type = FOUR_OF_A_KIND;
            else if ((max == 3 && sec == 2 && wildcard == 0) || (max == 3 && sec == 3 && wildcard == 1) )
                rounds[i].type = FULL_HOUSE;
            else if (max == 3)
                rounds[i].type = THREE_OF_A_KIND;
            else if (sec == 2 && wildcard == 0)
                rounds[i].type = TWO_PAIR;
            else if (max == 2)
                rounds[i].type = PAIR;
            else
                rounds[i].type = HIGH_CARD;

            memset(hand, 0, 12*sizeof(char));
            j = set = wildcard = 0;
            i++;
        } else if (ch == ' ') {
            set++;
        } else if (set)
            rounds[i].bid = rounds[i].bid*10 + ch-'0';
        else {
            if (isdigit(ch)) {
                rounds[i].hand[j] = ch - '0';
            } else if (ch == 'T') {
                rounds[i].hand[j] = 10;
            } else if (ch == 'J') {
                rounds[i].hand[j] = 1;
            } else if (ch == 'Q') {
                rounds[i].hand[j] = 11;
            } else if (ch == 'K') {
                rounds[i].hand[j] = 12;
            } else if (ch == 'A') {
                rounds[i].hand[j] = 13;
            }
            if (ch != 'J')
                hand[rounds[i].hand[j]-2]++;
            else {
                wildcard++;
                for (int i = 0; i < 12; i++)
                    hand[i]++;
            }
            j++;
        }
            
    }

    qsort(rounds, length, sizeof(order), sort);

    long sum = 0;
    for (int i = 0; i < length; i++) {
        sum += (1+i)*rounds[i].bid;
    }

    return sum;
}
