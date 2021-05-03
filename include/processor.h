#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>

#include "process.h"
using std::vector;

class Processor {
 public:
  Processor();
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  vector<Process>* processes_;
  long idle_;
  long nonIdle_;
  float util_; 
};

#endif
