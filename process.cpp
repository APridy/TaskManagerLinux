#include "process.h"
//#include "xtox.cpp"

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
    << "Memory: " << TextTransit::itomem(mem) << endl  << "Pid: " << pid << endl << "User: " << user << endl
    <<  "Threads: " << threads << endl << "Cmdline: " << cmdline << endl ;

}




