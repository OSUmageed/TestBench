//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc -o ./bin/cTest

struct tao{
    char mc;
    float mn[100];
};

int main(int argc, char *argv[])
{
    struct tao A;
    struct tao B;
    A.mc='A';
    B.mc='B';
    for (int k=0; k<100; k++)
    {
        A.mn[k]=k;
        B.mn[k]=k*k;
    }
    FILE *f;
    f = fopen("ioTest.dat", "w");
    fwrite(&A, sizeof(struct tao), 1, f);
    fwrite(&B, sizeof(struct tao), 1, f);
    fclose(f);
    return 0;
}
