#include <string>
#include <unistd.h>
#include "format.h"
#include <iomanip>

using std::string;
using std::to_string;
using std::setw;
using std::setfill;

string Format::ElapsedTime(long timeClocks) { 
  std::ostringstream result;
  long seconds=timeClocks;
  long h=seconds/3600;
  long m=seconds/60-h*60;
  long s=seconds-h*3600-m*60;
  result << std::setw(2) << std::setfill('0') << h << ":" <<std::setw(2) << std::setfill('0') << m << ":" << std::setw(2) << std::setfill('0') << s;
return result.str(); }
