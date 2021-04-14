#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    return util_;
}

// TODO: Return the command that generated this process
string Process::Command() { 
 return command_;
}
// TODO: Return this process's memory utilization
string Process::Ram() { 
 std::string ram = std::string(LinuxParser::Ram(pid_)); 
return ram;
}
// TODO: Return the user (name) that generated this process
string Process::User() { 
 std::string user =std::string (LinuxParser::User(pid_));
 return user_;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
 long int timeClocks = LinuxParser::UpTime(pid_); 
 long int seconds = timeClocks/sysconf(_SC_CLK_TCK);
 return seconds;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_nused]] once you define the function
bool Process::operator<(Process const& a) const {
  bool result = false;
  if(this->CpuUtilization() < a.CpuUtilization())
     result = true;
  return result;
}
bool Process::operator>(Process const& a) const {
  bool result = false;
  if(this->CpuUtilization() > a.CpuUtilization())
     result = true;
  return result;
} 
bool Process::Compare( Process const& va, Process const&  vb) const{
   bool result = false; 
   float a =va.CpuUtilization();
   float b =vb.CpuUtilization(); 
   if (a < b) 
      result=true;      
return result; }
void Process::SortProcesses(std::vector<Process>* v){
   sort(v->begin(), v->end());
}
