#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  vector<std::string> cpuStr = LinuxParser::CpuUtilization();
  auto it = cpuStr.begin();
  util_= std::stof(*it);
  return util_;
}
