#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream> 
#include <sstream>
#include <stdlib.h>
#include "linux_parser.h"

using std::stoi;
using std::stof;
using std::stol;
using std::string;
using std::to_string;
using std::vector;


template<typename T>
T LinuxParser::getValueFile(std::string const &path){
  std::string line;
  T value;
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  return value;
}
// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterOS) {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.emplace_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string os, key, value;
  string line;
  float mUsed,mTotal,mFree;
  //float mTotal,mUsed,Buffers; //Improve algorithm

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {  
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterMemTotalString) 
			mTotal=stof(value);
		if (key == filterMemFreeString)
			mFree=stof(value);
      }
    }
  }
  mUsed=1.0*(mTotal-mFree)/mTotal;
  return mUsed; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  long upTime;
  const string path =kProcDirectory + kUptimeFilename;
  upTime=getValueFile<long>(path);
  return upTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
	string line,user,nice,system,idle,cpu,iowait,irq;
	long tIdle,tPro;
    std::ifstream stream(kProcDirectory+kStatFilename);
	if (stream.is_open()){
		std::getline(stream,line);
        std::istringstream linestream(line);
		linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq;
     }
     tIdle=std::stol(idle)+std::stol(iowait);
     tPro=std::stol(user)+std::stol(nice)+std::stol(system);

return tPro-tIdle; 
}

// TODO: Read and return the number of active jiffies for a PID

long LinuxParser::ActiveJiffies(int pid) {
  long uptime,stime,cutime,cstime,active; 
  std::string property,line;
  std::string path=std::string(kProcDirectory+std::to_string(pid)+"/stat");
  std::ifstream stream(path);
   if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int i=1;
    while (linestream >> property){
      if(i == 14)
         uptime=std::stol(property);    
	  if(i == 15)
         stime=std::stol(property);
      if(i == 16)
        cutime=std::stol(property);
      if(i == 17)
        cstime=std::stol(property);
      i++;
    }
  }
  active=uptime+stime+cutime+cstime;

return active; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
    string line,user,nice,system,idle,cpu,iowait,irq;
    long tAct;
    std::ifstream stream(kProcDirectory+kStatFilename);
    if (stream.is_open()){
        std::getline(stream,line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq;
     }
    tAct=std::stol(user)+std::stol(nice)+std::stol(system);

return tAct; 
}
// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
    string line,user,nice,system,idle,cpu,iowait,irq;
    long tIdle;
    std::ifstream stream(kProcDirectory+kStatFilename);
    if (stream.is_open()){
        std::getline(stream,line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq;
     }
    tIdle=std::stol(idle)+std::stol(iowait); 
return tIdle; 
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> result = {};
  long Idle = IdleJiffies();
  result.emplace_back(std::to_string(Idle));
  long nonIdle = ActiveJiffies();
  result.emplace_back(std::to_string(nonIdle));

  return result;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
	const std::string path = std::string(kProcDirectory+kStatFilename);
    string line,key,value;
	int TotalProcesses=GetKey<int>(path,filterProcesses);
return TotalProcesses; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 

    string path = kProcDirectory+kStatFilename;
    int processes = GetKey<int>(path,filterRunningProcesses);
  return processes;
 }
template<typename T>
T LinuxParser::GetKey(std::string path,std::string keyValue){
  string line,key;
  T result,value;
  std::ifstream stream(path);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == keyValue){
			  result=value;
        } 
     }
    }
  }
  return result;
}
std::string LinuxParser::Command(int pid){
  std::string line;
  std::string path=std::string(kProcDirectory+std::to_string(pid)+"/cmdline");
  std::string result = getValueFile<string>(path);
  return result; 
}
std::string LinuxParser::Ram(int pid){
  std::string path=std::string(kProcDirectory+std::to_string(pid)+"/status");
  //I'm using VmData instead of VmSize 
  std::string key=std::string(filterProcMem);
  std::string memory=GetKey<string>(path,key);
  //long conversion validation
  char *p;
  char *charMem =&memory[0];
  long memoryMB = std::strtol(charMem,&p,10);
  if (*p)
     memoryMB =0; 
  else 
     memoryMB/=1024;

  std::string result = std::string(std::to_string(memoryMB));
  return result; 
}
std::string LinuxParser::Uid(int pid){ 
  std::string statusPath=std::string(kProcDirectory+std::to_string(pid)+"/status");
  std::string key=std::string(filterUID);
  string uid=GetKey<string>(statusPath,key);
  return uid;
}

std::string LinuxParser::User(int pid){
  std::string value,name,x,line,result;
//Uid
  std::string uid=Uid(pid);
//Username
  std::ifstream streamEtc(kPasswordPath);
  if (streamEtc.is_open()) {
    while (std::getline(streamEtc, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> x >> value) {
        if (uid==value)
           result=name;
      }
    }
  }
  return result; 
}
long int LinuxParser::UpTime(int pid){
  long int uptime;
  std::string property,line;
  std::string path=std::string(kProcDirectory+std::to_string(pid)+"/stat");
  std::ifstream stream(path);
   if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int i=1;
    while (linestream >> property){
      if (i == 14){
         uptime=std::stol(property);
         return uptime;
      }
      i++;
    }
  }
  return uptime; 
}
long int LinuxParser::ElapsedTime(int pid){

  long int uptime=UpTime();
  long int starttime,elapsed;
  std::string property,line;
  std::string path=std::string(kProcDirectory+std::to_string(pid)+"/stat");
  std::ifstream stream(path);
   if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int i=1;
    while (linestream >> property){
      if (i == 22){
         starttime=std::stol(property);
         
      }
      i++;
    }
  }
  elapsed= uptime - starttime/sysconf(_SC_CLK_TCK);
  return elapsed; 
}
