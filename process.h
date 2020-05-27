#ifndef PROCESS_H
#define PROCESS_H
#include "texttransit.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <termcap.h>
#include <sys/types.h>
#include <signal.h>

using namespace std;

class Process
{
private:
    string name;
    string user;
    string cmdline;
    int mem;
    int threads;
    int pid;
    double cpuper;
public:
    Process();
    Process(int);
    void set_name(string);
    void set_user(string);
    void set_cmdline(string);
    void set_mem(int);
    void set_threads(int);
    void set_pid(int);
    void set_cpuper(double);

    string get_name();
    string get_user();
    string get_cmdline();
    int get_mem();
    int get_threads();
    int get_pid();
    double get_cpuper();

    string extract_name();
    string extract_user();
    string extract_cmdline();
    int extract_mem();
    int extract_threads();
    int extract_pid();
    double extract_cpuper();

    void print_process();
};

#endif // PROCESS_H
