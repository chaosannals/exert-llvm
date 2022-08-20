#include <stdio.h>

extern int func(int a);

int main() {
    int num = 5;
    num = func(num);
    printf("%d \n", num);
    return 0;
}

