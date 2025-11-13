#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int frames[8];
    int pages[1000];

    for (int i = 0; i < 1000; i++) {
        int rando = rand() & 0x7FFF;
        pages[i] = rando >> 10;
        printf("%d\n", pages[i]);
    }
    return 0;
}