#include <string>

#include "format.h"
#include <math.h>

using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  int hh, mm, ss;
  string HH, MM, SS;
 hh= floor(seconds/3600);
  mm=floor((seconds-3600*hh)/60);
  ss=seconds-3600*hh-60*mm;
  if(hh<10){
    HH="0"+to_string(hh);
  }else{
   HH=to_string(hh);
  }
  if(mm<10){
    MM="0"+to_string(mm);
  }else{
   MM=to_string(mm);
  }
  if(ss<10){
    SS="0"+to_string(ss);
  }else{
   SS=to_string(ss);
  }
  return HH+":"+MM+":"+SS; 
}