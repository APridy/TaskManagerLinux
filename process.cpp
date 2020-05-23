#include "process.h"
//#include "xtox.cpp"

Process::Process()
{
    name = "";
    user = "";
    cmdline = "";    
    mem = 0;
    threads = 0;
    pid = 0;
}

Process::Process(int num)
{
    pid = num;
    name = extract_name();
    user = extract_user();
    cmdline = extract_cmdline();
    mem = extract_mem();
    threads = extract_threads();

}

void Process::set_name(string str) {
    name = str;
}

string Process::get_name() {
    return name;
}

string Process::extract_name() {
    string str = "cat /proc/";
    str += TextTransit::itoa(pid);
    str += "/comm 2> /dev/null";
    const char * c = str.c_str();
    str = TextTransit::systemExec(c);
    if(str.size())
    str.resize(str.size() - 1);
    else return "Unnamed";
    if(str == "TaskManagerSPOV") return "TaskManagerSPOVM";
    return str;
}

void Process::set_user(string str) {
    user = str;
}
string Process::get_user() {
    return user;
}

string Process::extract_user() {
    string str = "id -nu 2> /dev/null </proc/";
    str += TextTransit::itoa(pid);
    str += "/loginuid ";
    const char * c = str.c_str();
    str = TextTransit::systemExec(c);
    if(str.size() != 0)
    str.resize(str.size() - 1);
    else return "Unknown";
    return str;
}

void Process::set_cmdline(string str) {
    cmdline = str;
}

string Process::get_cmdline() {
    return cmdline;
}

string Process::extract_cmdline() {
    string str = "cat /proc/";
    str += TextTransit::itoa(pid);
    str += "/cmdline 2> /dev/null";
    const char * c = str.c_str();
    str = TextTransit::systemExec(c);
    if(!str.size()) return "Cmdline not found";
    return str;
}

void Process::set_mem(int num) {
    mem = num;
}

int Process::get_mem() {
    return mem;
}

int Process::extract_mem() {
    int i = 9;
    string str = "cat /proc/", mem;
    str += TextTransit::itoa(pid);
    str += "/status 2> /dev/null | grep RssAnon";
    const char * c = str.c_str();
    str = TextTransit::systemExec(c);
    if(!str.size()) return 0;
    while(str[i] != 'k' && str[i] != '\n') {
        if((str[i] != ' ')) {
            mem += str[i];
        }
        i++;
    }
    return TextTransit::atoi(mem);
}

void Process::set_threads(int num) {
    threads = num;
}

int Process::get_threads() {
    return threads;
}

int Process::extract_threads() {
    int i = 9;
    string str = "cat /proc/", threads;
    str += TextTransit::itoa(pid);
    str += "/status 2> /dev/null | grep Threads";
    const char * c = str.c_str();
    str = TextTransit::systemExec(c);
    if (str == "") return 0;
    while(str[i] != '\n'){
        if((str[i] != ' ')) {
           threads += str[i];
        }
        i++;
    }
    return TextTransit::atoi(threads);
}

void Process::set_pid(int num) {
    pid = num;
}

int Process::get_pid() {
   return pid;
}

void Process::print_process() {
    cout << "----------------" << endl << "Name: " << name << endl
    << "Memory: " << TextTransit::itomem(mem) << endl  << "Pid: " << pid << endl << "User: " << user << endl
    <<  "Threads: " << threads << endl << "Cmdline: " << cmdline << endl ;

}




