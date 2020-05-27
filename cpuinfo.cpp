#include "cpuinfo.h"


CPUInfo::CPUInfo()
{
    set_model(extract_model());
    set_cpu_num(extract_cpu_num());
    set_totalRAM(extract_totalRAM());
    set_totalRAM_usage(extract_totalRAM_usage());
    cpu_usage.resize(TextTransit::atoi(TextTransit::systemExec("cat /proc/cpuinfo | grep processor | wc -l")));
   // set_cpu_usage(extract_cpu_usage());
}

string CPUInfo::get_model() {
    return model;
}

string CPUInfo::extract_model() {
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
    return cpu_num;
}

int CPUInfo::extract_cpu_num() {
    return TextTransit::atoi(TextTransit::systemExec("cat /proc/cpuinfo | grep processor | wc -l"));
}

int CPUInfo::get_totalRAM() {
    return totalRAM;
}

int CPUInfo::extract_totalRAM() {
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

int CPUInfo::extract_totalRAM_usage() {
    string str,totalramusage;
    int i = 5;
    str = TextTransit::systemExec("free -m | grep Mem: ");
    while(str[i] == ' ') i++;
    while(str[i] != ' ') i++;
    while(str[i] == ' ') i++;

     while(str[i] != ' ') {
        totalramusage += str[i];
        i++;
    }

    return (TextTransit::atoi(totalramusage))*1024;
}


int CPUInfo::get_single_cpu_usage(int num) {
    return cpu_usage[num];
}

vector<int> CPUInfo::get_cpu_usage() {
    return cpu_usage;
}

vector<int> CPUInfo::extract_cpu_usage() {
    vector<int> CPUusage;
    string str,individual_cpu_usage;
    for(int i = 0; i < cpu_num; i++) {
    str = "mpstat -P ALL 1 1| grep \"Average:       \"";
    str += TextTransit::itoa(i);
    str = TextTransit::systemExec(str.c_str());
    individual_cpu_usage = "";
    int j = 1;
    for(int k = 0; k < 11;k++) {
       while(str[j] != ' ') j++;
       while(str[j] == ' ') j++;
    }

    while(str[j] != '.') {
            if(str[j] != ' ') individual_cpu_usage += str[j];
            j++;
    }

    CPUusage.push_back(100 - TextTransit::atoi(individual_cpu_usage));
    }
    return CPUusage;
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


void CPUInfo::refresh_info() {
     set_totalRAM(extract_totalRAM());
     set_totalRAM_usage(extract_totalRAM_usage());
     set_cpu_usage(extract_cpu_usage());
}

void CPUInfo::print_info() {
    cout << "Processor model: "<< model << endl << "Number of cores: "
         << cpu_num  << endl << "RAM: " << totalRAM << endl << "Memory usage: " << 100*totalRAM_usage/totalRAM << "%" << endl;
    for(int i = 0; i < cpu_num;i++) {
    cout << "CPU №" << i + 1 << " usage: " << cpu_usage[i] << "%" << endl;
    }
}





