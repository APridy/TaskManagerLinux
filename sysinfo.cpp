#include "sysinfo.h"


SysInfo::SysInfo()
{   
    totalmem = 0;
    refresh_process_array();
}

int SysInfo::get_cpuper(int pid) {
    int cputotal = 0,part = 0,utime = 0,stime = 0,cpuper,i = 0,spaces = 0;
    int cputotal_after = 0, utime_after = 0, stime_after = 0;
    string str;
    const char * c;
    str = "cat /proc/";
    str += TextTransit::itoa(pid);
    str += "/stat 2> dev_null";
    //////////////////////
        c = str.c_str();
        str = TextTransit::systemExec(c);

        if(str.size()) {

            i = 0;
            while(spaces < 13){
                if(str[i] == ' ') spaces++;
                i++;
            }
            //i++;

            while((str[i] != ' ')) {
                if((str[i] >= '0') && (str[i] <= '9')) {
                part *= 10;
                part += str[i] - 48;
                }
                if(str[i] == ' ') {
                utime += part;
                part = 0;
                }
                i++;
            }
            utime += part;

            i++;
            part = 0;

            while((str[i] != ' ')) {
                if((str[i] >= '0') && (str[i] <= '9')) {
                part *= 10;
                part += str[i] - 48;
                }
                if(str[i] == ' ') {
                stime += part;
                part = 0;
                }
                i++;
            }
            stime += part;
        }
        else { utime = 0; stime = 0;}

        part = 0;

        str = "cat /proc/stat | grep -w cpu";
        c = str.c_str();
        str = TextTransit::systemExec(c);
        i = 4;
        while((str[i] != '\n')) {
            if((str[i] >= '0') && (str[i] <= '9')) {
            part *= 10;
            part += str[i] - 48;
            }
            if(str[i] == ' ') {
            cputotal += part;
            part = 0;
            }
            i++;
        }
        cputotal += part;

        //////
        //usleep(200000);


        part = 0;
        i = 0;
        spaces = 0;

        str = "cat /proc/";
        str += TextTransit::itoa(pid);
        str += "/stat 2> dev_null";

        c = str.c_str();
        str = TextTransit::systemExec(c);

        if(str.size()) {

            i = 0;
            while(spaces < 13){
                if(str[i] == ' ') spaces++;
                i++;
            }
            //i++;

            while((str[i] != ' ')) {
                if((str[i] >= '0') && (str[i] <= '9')) {
                part *= 10;
                part += str[i] - 48;
                }
                if(str[i] == ' ') {
                utime_after += part;
                part = 0;
                }
                i++;
            }
            utime_after += part;

            i++;
            part = 0;

            while((str[i] != ' ')) {
                if((str[i] >= '0') && (str[i] <= '9')) {
                part *= 10;
                part += str[i] - 48;
                }
                if(str[i] == ' ') {
                stime_after += part;
                part = 0;
                }
                i++;
            }
            stime_after += part;
        }
        else { utime_after = 0; stime_after = 0;}

        part = 0;

        str = "cat /proc/stat | grep -w cpu";
        c = str.c_str();
        str = TextTransit::systemExec(c);
        i = 4;
        while((str[i] != '\n')) {
            if((str[i] >= '0') && (str[i] <= '9')) {
            part *= 10;
            part += str[i] - 48;
            }
            if(str[i] == ' ') {
            cputotal_after += part;
            part = 0;
            }
            i++;
        }
        cputotal_after += part;

    //cpuper =  100*(((utime_after - utime) + (stime_after - stime))/(cputotal_after - cputotal));

    return cputotal;
}

string SysInfo::get_name(int pid){
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

string SysInfo::get_cmdline(int pid){
    string str = "cat /proc/";
    str += TextTransit::itoa(pid);
    str += "/cmdline 2> /dev/null";
    const char * c = str.c_str();
    str = TextTransit::systemExec(c);
    if(!str.size()) return "Cmdline not found";
    return str;
}

string SysInfo::get_user(int pid){
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

int SysInfo::get_mem(int pid) {
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

int SysInfo::get_threads(int pid){
    int i = 9;
    string str = "cat /proc/", threads;
    str += TextTransit::itoa(pid);
    str += "/status 2> /dev/null | grep Threads";
    const char * c = str.c_str();
    str = TextTransit::systemExec(c);
    while(str[i] != '\n'){
        if((str[i] != ' ')) {
           threads += str[i];
        }
        i++;
    }
    return TextTransit::atoi(threads);
}

int SysInfo::get_totalmem(){
    return totalmem;
}

vector<Process> SysInfo::get_process_array() {
    return process_array;
}

void SysInfo::refresh_process_array(){
    string str;
    int i = 0,process_amount = 0,pid = 0;
    str = TextTransit::systemExec("ls /proc");

    while( ( (str[i] >= '0') && (str[i] <= '9') ) || (str[i] == '\n')) {
        if((str[i] >= '0') && (str[i] <= '9')) {
        pid *= 10;
        pid += str[i] - 48;
       }
        if(str[i] == '\n') {
            Process pr;
            totalmem += get_mem(pid);
            pr.set_pid(pid);
            pr.set_mem(get_mem(pid));
            pr.set_name(get_name(pid));

            pr.set_threads(get_threads(pid));
            pr.set_user(get_user(pid));

            pr.set_cmdline(get_cmdline(pid));
            pr.set_cpuper(get_cpuper(pid));
            process_array.push_back(pr);
            pid = 0;
            process_amount++;
        }
        i++;
    }
}

void SysInfo::print_processes(){
    for(int i = 0; i < process_array.size(); i++) {
    process_array[i].print_process();
    }
    cout << totalmem << endl;
}
