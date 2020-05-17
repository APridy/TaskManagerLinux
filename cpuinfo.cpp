#include "cpuinfo.h"


CPUInfo::CPUInfo()
{
    set_model(get_model());
    set_cpu_num(get_cpu_num());
    totalCPU = 0;
    totalCPU_usage = 0;
    cpu_usage.resize(atoi(systemExec("cat /proc/cpuinfo | grep processor | wc -l")));
}

int CPUInfo::atoi(string str) {
    int num = 0;
    for(int i = 0; i < str.size() ; i++){
        if (str[i] == '\n') return num;
        num *= 10;
        num += str[i] - 48;
    }
   return num;
}

string CPUInfo::itoa(int num){
    string str;
    int div = 1;
    while(num/div > 9) div *= 10;
    while(div != 0) {
        str += (num/div) + 48;
        num %= div;
        div /= 10;
    }
   return str;
}

string CPUInfo::systemExec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);

    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
    if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
    result += buffer.data();
    }
    return result;
}

string CPUInfo::get_model() {
    string str,model_name;
    int i = 13;
    str = systemExec("cat /proc/cpuinfo | grep name ");
    while(str[i] != 'k' && str[i] != '\n') {
        if((str[i] != ' ')) {
            model_name += str[i];
        }
        i++;
    }
    return model_name;
}

int CPUInfo::get_cpu_num() {
    return atoi(systemExec("cat /proc/cpuinfo | grep processor | wc -l"));
}

int CPUInfo::get_totalCPU() {
    string str,totalcpu;
    int i = 12;
    str = systemExec("cat /proc/meminfo | grep MemTotal ");
    while(str[i] != 'k' && str[i] != '\n') {
        if((str[i] != ' ')) {
            totalcpu += str[i];
        }
        i++;
    }
    return atoi(totalcpu);
}

int CPUInfo::get_totalCPU_usage() {
    return totalCPU_usage;
}

vector<int> CPUInfo::get_cpu_usage(int num) {
    vector<int> CPUusage;
    CPUusage.resize(num);
    string str,individual_cpu_usage;
    for(int i = 0; i < num; i++) {
    str = "mpstat -P ALL | grep \"M    \"";
    str += itoa(i);
    str = systemExec(str.c_str());
    individual_cpu_usage = "";
        for(int j = 19; j < 21;j++){
            individual_cpu_usage += str[j];
        }
    CPUusage[i] = atoi(individual_cpu_usage);
    }
    return CPUusage;
}

void CPUInfo::set_model(string str) {
    model = str;
}

void CPUInfo::set_cpu_num(int num) {
    cpu_num = num;
}

void CPUInfo::set_totalCPU(int num) {
    totalCPU = num;
}

void CPUInfo::set_totalCPU_usage(int num) {
    totalCPU_usage = num;
}

void CPUInfo::set_cpu_usage(vector<int> vect) {
    cpu_usage = vect;
}


void CPUInfo::refresh_info(SysInfo sysinfo) {
     set_totalCPU(get_totalCPU());
     set_totalCPU_usage(sysinfo.get_totalmem());
     set_cpu_usage(get_cpu_usage(cpu_num));
}

void CPUInfo::print_info() {
    cout << "Processor model: "<< model << endl << "Number of cores: "
         << cpu_num  << endl << "RAM: " << totalCPU << endl << "Memory usage: " << 100*totalCPU_usage/totalCPU << "%" << endl;
    for(int i = 0; i < cpu_num;i++) {
    cout << "CPU №" << i + 1 << " usage: " << cpu_usage[i] << "%" << endl;
    }
}





