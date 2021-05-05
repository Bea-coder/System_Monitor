#include <string>
#include <unistd.h>
#include "format.h"
#include <iomanip>

using std::string;
using std::to_string;
using std::setw;
using std::setfill;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long timeClocks) { 
  std::ostringstream result;
  long seconds=timeClocks;
  int h=seconds/3600;
  int m=seconds/60-h*60;
  int s=seconds-h*3600-m*60;
  //string result{to_string(h)+"::"+to_string(m)+"::"+to_string(s)};
  result << std::setw(2) << std::setfill('0') << h << ":" <<std::setw(2) << std::setfill('0') << m << ":" << std::setw(2) << std::setfill('0') << s;
return result.str(); }
