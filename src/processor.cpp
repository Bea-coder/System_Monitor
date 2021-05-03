#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
// TODO: Return the aggregate CPU utilization
Processor::Processor(){
 vector<std::string> cpuStr =  LinuxParser::CpuUtilization();
 long idle = std::stol(cpuStr[0]);
 long nonIdle = std::stol(cpuStr[1]);
 idle_=idle;
 nonIdle_=nonIdle;
}

float Processor::Utilization() {
  vector<std::string> cpuStr = LinuxParser::CpuUtilization();

  long idle= std::stol(cpuStr[0]);
  long nonIdle= std::stol(cpuStr[1]);

  long totalPrev= idle_+nonIdle_;
  long total= idle+nonIdle;
  long deltaTotal = total-totalPrev;
  long deltaIdle = idle-idle_;

  util_=1.0*(deltaTotal - deltaIdle)/deltaTotal;
  return util_;
}
