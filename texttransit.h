#ifndef TEXTTRANSIT_H
#define TEXTTRANSIT_H
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>

using namespace std;

class TextTransit
{
public:
    TextTransit();
    static string systemExec(const char* cmd);
    static string itoa(int);
    static int atoi(string);
    static string itomem(int);
    static string dtoa(double,int);
};

#endif // TEXTTRANSIT_H
