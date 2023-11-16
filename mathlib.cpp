// mathlib.cpp
#include <cstdio>
#include "mathlib.h"

// Declare a static variable
static int persistentVariable = 0;

extern "C" {



    int add(int a, int b) {
      
        persistentVariable++;


        A::test();
        return a + b;
    }

    char* subtract(char* ba) {
        printf("Now value is %d %02x %02x %02x %02x\n", persistentVariable, ba[0], ba[1], ba[2], ba[3]);
        char* res = new char[4];
res[0] = 'a';
res[1] = 'b';
res[2] = 'c';
res[3] = 'd';
        return res;
    }




void A::test()
{
printf("TEST\n");
}
}

//void A::test()
//{
//printf("TEST\n");
//}
