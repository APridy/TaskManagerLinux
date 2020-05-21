#ifndef CPUINFO_H
#define CPUINFO_H
#include<sysinfo.h>

class CPUInfo
{
private:
    string model;
    int cpu_num;
    int totalRAM;
    int totalRAM_usage;
    vector<int> cpu_usage;
public:
    CPUInfo();
    void refresh_info(SysInfo sysinfo);

    string get_model();
    int get_cpu_num();
    int get_totalRAM();
    int get_totalRAM_usage();
    int get_single_cpu_usage(int);
    vector<int> get_cpu_usage(int amount);

    void set_model(string);
    void set_cpu_num(int);
    void set_totalRAM(int);
    void set_totalRAM_usage(int);
    void set_cpu_usage(vector<int>);

    void print_info();

};

#endif // CPUINFO_H
