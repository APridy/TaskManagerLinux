#include "cpuinfo.h"


CPUInfo::CPUInfo()
{
    set_model(get_model());
    set_cpu_num(get_cpu_num());
    totalRAM = 0;
    totalRAM_usage = 0;
    cpu_usage.resize(TextTransit::atoi(TextTransit::systemExec("cat /proc/cpuinfo | grep processor | wc -l")));
}


string CPUInfo::get_model() {
    string str,model_name;
    int i = 13;
    str = TextTransit::systemExec("cat /proc/cpuinfo | grep name ");
    while(str[i] != 'k' && str[i] != '\n') {
        if((str[i] != ' ')) {
            model_name += str[i];
        }
        i++;
    }
    return model_name;
}

int CPUInfo::get_cpu_num() {
    return TextTransit::atoi(TextTransit::systemExec("cat /proc/cpuinfo | grep processor | wc -l"));
}

int CPUInfo::get_totalRAM() {
    string str,totalram;
    int i = 12;
    str = TextTransit::systemExec("cat /proc/meminfo | grep MemTotal ");
    while(str[i] != 'k' && str[i] != '\n') {
        if((str[i] != ' ')) {
            totalram += str[i];
        }
        i++;
    }
    return TextTransit::atoi(totalram);
}

int CPUInfo::get_totalRAM_usage() {
    return totalRAM_usage;
}

vector<int> CPUInfo::get_cpu_usage(int num) {
    vector<int> CPUusage;
    CPUusage.resize(num);
    string str,individual_cpu_usage;
    for(int i = 0; i < num; i++) {
    str = "mpstat -P ALL | grep \"M    \"";
    str += TextTransit::itoa(i);
    str = TextTransit::systemExec(str.c_str());
    individual_cpu_usage = "";
    int j = 18;
        while(str[j] != '.') {
            if(str[j] != ' ') individual_cpu_usage += str[j];
            j++;
        }
    CPUusage[i] = TextTransit::atoi(individual_cpu_usage);
    }
    return CPUusage;
}

int CPUInfo::get_single_cpu_usage(int num) {
    return cpu_usage[num];
}

void CPUInfo::set_model(string str) {
    model = str;
}

void CPUInfo::set_cpu_num(int num) {
    cpu_num = num;
}

void CPUInfo::set_totalRAM(int num) {
    totalRAM = num;
}

void CPUInfo::set_totalRAM_usage(int num) {
    totalRAM_usage = num;
}

void CPUInfo::set_cpu_usage(vector<int> vect) {
    cpu_usage = vect;
}


void CPUInfo::refresh_info(SysInfo sysinfo) {
     set_totalRAM(get_totalRAM());
     set_totalRAM_usage(sysinfo.get_totalmem());
     set_cpu_usage(get_cpu_usage(cpu_num));
}

void CPUInfo::print_info() {
    cout << "Processor model: "<< model << endl << "Number of cores: "
         << cpu_num  << endl << "RAM: " << totalRAM << endl << "Memory usage: " << 100*totalRAM_usage/totalRAM << "%" << endl;
    for(int i = 0; i < cpu_num;i++) {
    cout << "CPU №" << i + 1 << " usage: " << cpu_usage[i] << "%" << endl;
    }
}





