#include "process.h"

Process::Process()
{
    name = "";
    user = "";
    cmdline = "";
    cpuper = 0;
    mem = 0;
    threads = 0;
    pid = 0;
}

string Process::itoa(int num){
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

string Process::dtoa(double dnum,int number_of_characters){
   // return std::to_string(dnum);
    int num = dnum,afterdot;
    dnum -= num;
    string str;
    str = itoa(num);
    if(number_of_characters > 0) {
        str += ".";
        for(int i = 0; i < number_of_characters; i++) {
            dnum *= 10;
            afterdot = dnum + 48;
            num = dnum;
            dnum -= num;
            str += afterdot;
        }
    }
    return str;
}


string Process::itomem(int num) {
    double dnum = num;
    int number_of_characters_after_dot = 0;
    string str,measurment = " Kb";

    if(dnum < 0) return "Incorrect memory";
    if(dnum > 1024) { dnum /= 1024; number_of_characters_after_dot++; measurment = " Mb"; }
    if(dnum > 1024) { dnum /= 1024; number_of_characters_after_dot++; measurment = " Gb"; }

    str += dtoa(dnum,number_of_characters_after_dot);

    str += measurment;
    return str;
}

void Process::set_name(string str) {
    name = str;
}

string Process::get_name() {
   return name;
}

void Process::set_user(string str) {
    user = str;
}

string Process::get_user() {
   return user;
}

void Process::set_cmdline(string str) {
    cmdline = str;
}

string Process::get_cmdline() {
   return cmdline;
}

void Process::set_cpuper(int num) {
    cpuper = num;
}

int Process::get_cpuper() {
   return cpuper;
}

void Process::set_mem(int num) {
    mem = num;
}

int Process::get_mem() {
   return mem;
}

void Process::set_threads(int num) {
    threads = num;
}

int Process::get_threads() {
   return threads;
}

void Process::set_pid(int num) {
    pid = num;
}

int Process::get_pid() {
   return pid;
}

void Process::print_process() {
    cout << "----------------" << endl << "Name: " << name << endl << "Cpu percentage: " << cpuper << endl
    << "Memory: " << itomem(mem) << endl  << "Pid: " << pid << endl << "User: " << user << endl
    <<  "Threads: " << threads << endl << "Cmdline: " << cmdline << endl ;

}




