#ifndef CPUINFO_H
#define CPUINFO_H
#include<sysinfo.h>

class CPUInfo
{
private:
    string model;
    int cpu_num;
    int totalCPU;
    int totalCPU_usage;
    vector<int> cpu_usage;
public:
    CPUInfo();
    void refresh_info(SysInfo sysinfo);
    string systemExec(const char* cmd);
    int atoi(string);
    string itoa(int);

    string get_model();
    int get_cpu_num();
    int get_totalCPU();
    int get_totalCPU_usage();
    vector<int> get_cpu_usage(int);

    void set_model(string);
    void set_cpu_num(int);
    void set_totalCPU(int);
    void set_totalCPU_usage(int);
    void set_cpu_usage(vector<int>);

    void print_info();

};

#endif // CPUINFO_H
