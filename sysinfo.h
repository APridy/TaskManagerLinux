#ifndef SYSINFO_H
#define SYSINFO_H
#include <string>
#include <stdio.h>
#include <vector>
#include <memory>
#include <iostream>
#include "process.h"

using namespace std;

class SysInfo
{
private:
    vector<Process> process_array;
    int totalmem;
public:
    SysInfo();
    void refresh_process_array();

    vector<Process> get_process_array();
    int get_mem(int);
    int get_cpuper(int);
    int get_threads(int);
    int get_totalmem();
    string get_name(int);
    string get_cmdline(int);
    string get_user(int);
    void print_processes();

};

#endif // SYSINFO_H
