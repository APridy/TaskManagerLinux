#ifndef PROCESS_H
#define PROCESS_H
#include "texttransit.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Process
{
private:
    string name;
    string user;
    string cmdline;
    int cpuper;
    int mem;
    int threads;
    int pid;
public:
    Process();

    void set_name(string);
    void set_user(string);
    void set_cmdline(string);
    void set_cpuper(int);
    void set_mem(int);
    void set_threads(int);
    void set_pid(int);

    string get_name();
    string get_user();
    string get_cmdline();
    int get_cpuper();
    int get_mem();
    int get_threads();
    int get_pid();

    void print_process();
};

#endif // PROCESS_H
