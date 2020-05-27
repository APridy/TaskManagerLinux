#include "sysinfo.h"


SysInfo::SysInfo()
{   
    refresh_process_array();
}


vector<Process> SysInfo::get_process_array() {
    return process_array;
}

void SysInfo::refresh_process_array(){
    string str;
    int i = 0,pid = 0;
    str = TextTransit::systemExec("ls /proc");

    while( ( (str[i] >= '0') && (str[i] <= '9') ) || (str[i] == '\n')) {
        if((str[i] >= '0') && (str[i] <= '9')) {
        pid *= 10;
        pid += str[i] - 48;
       }
        if(str[i] == '\n') {
            Process pr(pid);
            process_array.push_back(pr);
            pid = 0;
        }
        i++;
    }
}

void SysInfo::delete_process_array(){
    for(int i = process_array.size() ; i > 0 ; i--)
    {
        process_array.pop_back();
    }

}

void SysInfo::print_processes(){
    for(uint i = 0; i < process_array.size(); i++) {
    process_array[i].print_process();
    }

}
