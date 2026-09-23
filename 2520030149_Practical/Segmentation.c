#include <stdio.h>

int main() {
    int *ptr = NULL;

    printf("Attempting to access invalid memory...\n");

    *ptr = 10;

    return 0;
}