#include <algorithm>  // for sort
#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }
void System::SortProcesses(std::vector<Process>* v){
   sort(v->begin(), v->end(),std::greater<Process>());
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
 vector<int> PIDs=LinuxParser::Pids();
 float util;
 long int activeTime, elapsed;
 processes_.clear();
 for (auto i = PIDs.begin(); i != PIDs.end(); ++i){
   std::string user=std::string(LinuxParser::User(*i));
   std::string command=LinuxParser::Command(*i);
   util=0.0;
   activeTime = LinuxParser::ActiveJiffies(*i)/sysconf(_SC_CLK_TCK);
   elapsed = LinuxParser::ElapsedTime(*i);
    if(elapsed != 0)
       util=1.0*activeTime/elapsed;
    else
       util=0.0;
   Process newProcess(*i,user,command,util);
   processes_.push_back(newProcess);
 }
 System::SortProcesses(&processes_);

return processes_; }
// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return  LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
