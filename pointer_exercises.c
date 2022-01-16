#include <stdio.h>
#include <stdlib.h>

void f(void)
{
    int a[4];
    int *b = malloc(16);
    int *c;
    int i;

    printf("1: a = %p, b = %p, c = %p\n", a, b, c);

    c = a;
    for (i = 0; i < 4; i++)
	a[i] = 100 + i;
    c[0] = 200;
    printf("2: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c[1] = 300;
    *(c + 2) = 301;
    3[c] = 302;
    printf("3: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c = c + 1;
    *c = 400;
    printf("4: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    // printf("*c = 0x%08x\n", (int)*c);
    c = (int *) ((char *) c + 1);
    // printf("sizeof int: %lu, sizeof char: %lu\n", sizeof(a[1]), sizeof(char)); // int has 4 bytes, char has 1
    // printf("*c = 0x%08x\n", *c);
    *c = 500;
    // printf("5: a[0] = 0x%08x, a[1] = 0x%08x, a[2] = 0x%08x, a[3] = %d\n",
    printf("5: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    b = (int *) a + 1;
    c = (int *) ((char *) a + 1);
    printf("6: a = %p, b = %p, c = %p\n", a, b, c);

    // int* p = (int*)100;
    // printf("(int)p + 1 = %d, (int)(p + 1) = %d\n", (int)p + 1, (int)(p + 1));
}

int main(int ac, char **av)
{
    f();
    return 0;
}