#include <string>
#include <unistd.h>
#include "format.h"

using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long timeClocks) { 
  long seconds=timeClocks/sysconf(_SC_CLK_TCK);
  int h=seconds/3600;
  int m=seconds/60-h*60;
  int s=seconds-h*3600-m*60;
  string result{to_string(h)+"::"+to_string(m)+"::"+to_string(s)};
 
return result; }
