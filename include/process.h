#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid,std::string user,std::string command,float util){ 
  pid_=pid; 
  user_=user;
  command_=command;
  util_=util;
  };
//  Process(int pid){pid_=pid;};
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                    // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  bool operator>(Process const& a) const;  // TODO: See src/process.cpp
  bool Compare( Process const& a, Process const& b) const;
  void SortProcesses(std::vector<Process>* v );

  // TODO: Declare any necessary private members
 private:
  int pid_;
  float util_;
  std::string user_;
  std::string command_;
};

#endif
